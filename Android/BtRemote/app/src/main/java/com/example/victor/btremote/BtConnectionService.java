package com.example.victor.btremote;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Context;
import android.os.Handler;
import android.os.ParcelUuid;
import android.util.Log;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Arrays;
import java.util.UUID;

/**
 * Created by Victor on 06.05.2015.
 */
public class BtConnectionService
{
    private static final String NAME_SECURE = "BtRemoteControl";
    private static final UUID   BT_SERIAL_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
    private static final String LOG_TAG     = "BtRemoteLogs";
    private static final String ROVER_MAC   = "98:D3:31:80:41:76";

    private final BluetoothAdapter mAdapter;
    private final Handler          mUiHandler;
    private BluetoothSocket mBtSocket;
    private ConnectionThread mConnectionThread;

    private boolean mIsConnected;

    private int     mLeftMotorPower;
    private int     mRightMotorPower;
    private boolean mLeftReverse;
    private boolean mRightReverse;



    public class ENoBluetooth extends Exception {};
    public class ENoDevice    extends Exception {};

    public enum Motor  { eLeft, eRight };

    BtConnectionService(Context context, Handler uiHandler) throws Exception
    {
        mAdapter = BluetoothAdapter.getDefaultAdapter();
        if (mAdapter == null || !mAdapter.isEnabled())
            throw new ENoBluetooth();

        Log.d(LOG_TAG, "Bluetooth available");

        mAdapter.cancelDiscovery();
        Log.d(LOG_TAG, "Discovery canceled");

        BluetoothDevice device = mAdapter.getRemoteDevice(ROVER_MAC);
        mBtSocket = device.createRfcommSocketToServiceRecord(BT_SERIAL_UUID);
        mBtSocket.connect();

        Log.d(LOG_TAG, "Connected to: " + device.getName());

        mUiHandler = uiHandler;
        mConnectionThread = new ConnectionThread(mBtSocket, mUiHandler);
        mConnectionThread.start();
    }

    void close()
    {
        mLeftMotorPower = mRightMotorPower = 0;
        mLeftReverse = mRightReverse = false;

        if(mConnectionThread != null)
        {
            mConnectionThread.cancel();
            mConnectionThread = null;
        }
    }

    public void setMotorState(Motor which, int power, boolean isReverse)
    {
        switch (which)
        {
            case eLeft:
                mLeftMotorPower = power;
                mLeftReverse    = isReverse;
                break;

            case eRight:
                mRightMotorPower = power;
                mRightReverse    = isReverse;
                break;

            default:
                //@todo - error message
                break;
        }

        Log.d(LOG_TAG, String.format("State %s - power: %d, isReverse: %s;", which.toString(), power, String.valueOf(isReverse)));
        onChangesMade();
    }

    private void onChangesMade()
    {
        byte[] packet = new byte[7];

        byte rightPower = (byte)('0' + (mLeftMotorPower * 9 / 255));
        byte leftPower  = (byte)('0' + (mRightMotorPower * 9 / 255));
        byte rightReverse = mRightReverse ? (byte)'1' : (byte)'0';
        byte leftReverse  = mLeftReverse  ? (byte)'1' : (byte)'0';

        packet[0] = packet[2] = rightPower; // front right
        packet[1] = packet[3] = leftPower;  // front left
        packet[4] = rightReverse;
        packet[5] = leftReverse;
        packet[6] = (byte)'0'; // TODO - checksum

        Log.d(LOG_TAG, new String(packet));

        // @todo
        if(mConnectionThread == null)
        {
            Log.d(LOG_TAG, "No connection");
            return;
        }

        mConnectionThread.write(packet);
    }


    private class ConnectionThread extends Thread
    {
        private BluetoothSocket mBtSocket;
        private OutputStream    mOutStream;
        private InputStream     mInStream;
        private Handler         mUiHandler;

        private boolean mShouldStop;

        ConnectionThread(BluetoothSocket socket, Handler uiHandler) throws Exception
        {
            mBtSocket  = socket;
            mOutStream = mBtSocket.getOutputStream();
            mInStream  = mBtSocket.getInputStream();
            mUiHandler = uiHandler;
            Log.d(LOG_TAG, "Writer stream created");
        }

        public void cancel()
        {
            if(!isWorking())
                return;

            mShouldStop = true;
            clear();
        }

        private void clear()
        {
            if(!isWorking())
                return; // already stopped

            try {mOutStream.close();} catch (Exception e)    {Log.e(LOG_TAG, "Thread: " + e.getMessage());}
            mOutStream = null;

            try {mInStream.close();} catch (Exception e)     {Log.e(LOG_TAG, "Thread: " + e.getMessage());}
            mInStream = null;

            try {mBtSocket.close();} catch (Exception e)     {Log.e(LOG_TAG, "Thread: " + e.getMessage());}
            mBtSocket = null;
        }

        public void write(byte[] buffer)
        {
            try
            {
                mOutStream.write(buffer);

                // Share the sent message back to the UI Activity
                mUiHandler.obtainMessage(Constants.MESSAGE_WRITE, -1, -1, buffer)
                          .sendToTarget();
            }
            catch (IOException e)
            {
                Log.e(LOG_TAG, "Exception during write", e);
            }
        }

        public void run()
        {
            byte[] buffer = new byte[256];
            int bytes;

            while(!mShouldStop)
            {
                try
                {
                    Arrays.fill(buffer, (byte)0);
                    bytes = mInStream.read(buffer);

                    mUiHandler.obtainMessage(Constants.MESSAGE_READ, bytes, -1, Arrays.copyOf(buffer, bytes)).sendToTarget();
                }
                catch(IOException e)
                {
                    Log.e(LOG_TAG, "Reader: " + e.getMessage());
                    break;
                }
            }

            clear();
        }

        public boolean isWorking()
        {
            return mOutStream != null && mInStream != null;
        }
    }

}
