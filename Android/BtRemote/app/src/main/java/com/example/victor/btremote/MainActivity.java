package com.example.victor.btremote;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.MotorSeekBar;
import android.widget.SeekBar;
import android.widget.Toast;


public class MainActivity extends Activity
{
    private final int REQUEST_ENABLE_BT = 1;
    private final static String LOG_TAG = "BtRemoteLogs";

    private BtConnectionService mService           = null;
    private MotorSeekBar        mLeftMotorControl  = null;
    private MotorSeekBar        mRightMotorControl = null;
    private Handler             mHandler           = null;

    class MotorControlListener implements SeekBar.OnSeekBarChangeListener
    {
        private final BtConnectionService.Motor mWhich;
        private final BtConnectionService       mBtConnection;

        MotorControlListener(BtConnectionService btConnection, BtConnectionService.Motor which)
        {
            mWhich        = which;
            mBtConnection = btConnection;
        }

        @Override
        public void onProgressChanged(SeekBar seekBar, int progress, boolean isFromUser)
        {
            MotorSeekBar motorSeekBar = (MotorSeekBar)seekBar;

            int     neutralPosition = motorSeekBar.getNeutralPos();
            boolean isReverse = progress < neutralPosition;
            int     power = progress > neutralPosition
                            ? /* towards */ progress - neutralPosition
                            : /* backwards */ neutralPosition - progress;

            startCommunication();

            mBtConnection.setMotorState(mWhich, power, isReverse);
        }

        @Override public void onStartTrackingTouch(SeekBar seekBar) { }
        @Override public void onStopTrackingTouch(SeekBar seekBar)  { }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
        mLeftMotorControl = (MotorSeekBar) findViewById(R.id.seekBarLeft);
        mRightMotorControl = (MotorSeekBar) findViewById(R.id.seekBarRight);

        startCommunication();
    }

    @Override
    protected void onStart()
    {
        super.onStart();
        startCommunication();
    }

    private void startCommunication()
    {
        if(mService != null && mService.isWorking())
            return;  // already done

        try
        {
            Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);

            if(mService != null)
            {
                mService.close();
                mService = null;
            }

            mHandler = new Handler() {
                public void handleMessage(android.os.Message msg) {
                    switch (msg.what) {
                        case Constants.MESSAGE_READ:
                            byte[] readBuf = (byte[]) msg.obj;
                            String strIncom = new String(readBuf, 0, msg.arg1);
                            Log.d(LOG_TAG, "< Read: \n" + strIncom);
                            break;
                    }
                };
            };

            mService = new BtConnectionService(this, mHandler);

            mLeftMotorControl.setOnSeekBarChangeListener (new MotorControlListener(mService, BtConnectionService.Motor.eLeft));
            mRightMotorControl.setOnSeekBarChangeListener(new MotorControlListener(mService, BtConnectionService.Motor.eRight));
        }
        catch (BtConnectionService.ENoBluetooth e)
        {
            Toast.makeText(this, R.string.no_bluetooth, Toast.LENGTH_SHORT).show();
        }
        catch (BtConnectionService.ENoDevice e)
        {
            Toast.makeText(this, getString(R.string.no_device), Toast.LENGTH_SHORT).show();
        }
        catch (Exception e)
        {
            String message = "Exception: " + e.getMessage();
            Log.e(LOG_TAG, message);
            Toast.makeText(this, message, Toast.LENGTH_SHORT).show();
        }
    }

    @Override
    protected void onStop()
    {
        super.onStop();
        Log.d(LOG_TAG, "Stop");
        if(mService != null)
        {
            mService.close();
            mService = null;
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
