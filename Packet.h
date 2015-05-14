#pragma once
#ifndef _PACKET_H_
#define _PACKET_H_
#include "Arduino.h"

struct Packet
{
  char m_frontRight;
  char m_frontLeft;
  char m_rearRight;
  char m_rearLeft;
  char m_rightDirection;
  char m_leftDirection;
  char m_checkSum;
  
  Packet() : m_frontRight(0), m_frontLeft(0), m_rearRight(0), m_rearLeft(0), m_rightDirection(0), m_leftDirection(0), m_checkSum(0)       {}

  static const Packet nullPacket;  
  static bool isValidChar(char c)         { return c >= '0' && c <= '9'; }
  bool isValid() const                    { return isValidChar(m_frontRight) && isValidChar(m_frontLeft) && isValidChar(m_rearRight) && isValidChar(m_rearLeft) 
                                                && isValidChar(m_rightDirection) && isValidChar(m_leftDirection); }

  static bool isAvailable(Stream& stream) { return stream.available() >= sizeof(Packet); }
  static bool read(Stream& stream, Packet& p) // read packet from stream, if available. return true if read succesfully
  {
     stream.print(stream.available()); stream.print(F(" bytes available; ")); stream.print(sizeof(Packet)); stream.println(F(" bytes needed")); 
     if (!isAvailable(stream))
         return false;
     
     char* buffer = (char*)&p;
     for(int i=0; i<sizeof(p); ++i)
         buffer[i] = stream.read();
      
     stream.println(F("Command read successfully"));
     return true;
  } 
};


#endif // _PACKET_H_
