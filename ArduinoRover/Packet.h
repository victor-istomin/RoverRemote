#pragma once
#ifndef _PACKET_H_
#define _PACKET_H_
#include "Arduino.h"

struct Packet
{
  static const char START_SIGNATURE = 'S'; 
  static const char END_SIGNATURE   = 'E'; 
  
  char m_startByte;  // == START_SIGNATURE
  char m_frontRight;
  char m_frontLeft;
  char m_rearRight;
  char m_rearLeft;
  char m_rightDirection;
  char m_leftDirection;
  char m_endSignature;
  
  void dump(Stream& s) const
  {
    s.print("0 SB: "); s.println(m_startByte);
    s.print("1 FR: "); s.println(m_frontRight);
    s.print("2 FL: "); s.println(m_frontLeft);
    s.print("3 RR: "); s.println(m_rearRight);
    s.print("4 RL: "); s.println(m_rearLeft);
    s.print("5 DR: "); s.println(m_rightDirection);
    s.print("6 DL: "); s.println(m_leftDirection);
    s.print("7 EB: "); s.println(m_endSignature);
  }
  
  Packet() : m_startByte(0), m_frontRight(0), m_frontLeft(0), m_rearRight(0), m_rearLeft(0), m_rightDirection(0), m_leftDirection(0), m_endSignature(0)       {}

  static bool isValidChar(char c)         { return c >= '0' && c <= '9'; }
  bool isValid() const                    { return m_startByte == START_SIGNATURE && m_endSignature == END_SIGNATURE
                                                && isValidChar(m_frontRight) && isValidChar(m_frontLeft) && isValidChar(m_rearRight) && isValidChar(m_rearLeft) 
                                                && isValidChar(m_rightDirection) && isValidChar(m_leftDirection); }

  static bool isAvailable(Stream& stream) { return stream.available() >= sizeof(Packet) && stream.peek() == START_SIGNATURE; }
  static bool read(Stream& stream, Packet& p) // read packet from stream, if available. return true if read succesfully
  {
     if(!stream.available())
     {
         Serial.println("Nothing available");      
     }
     else
     {
       Serial.print("Available "); Serial.print(stream.available()); Serial.print(" bytes:");
       Serial.print(stream.peek()); Serial.println("...");
     }
     
     if (!isAvailable(stream))
     {
         if (stream.available())
         {
             stream.print(stream.available()); stream.print(F(" bytes available; ")); stream.print(sizeof(Packet)); stream.println(F(" bytes needed")); 
         }
   
         return false;
     }
     
     stream.print(F("OK:"));
     char* buffer = (char*)&p;
     for(int i=0; i<sizeof(p); ++i)
         stream.print(buffer[i] = stream.read());
      
     stream.println(F(";"));
     return true;
  } 
};


#endif // _PACKET_H_
