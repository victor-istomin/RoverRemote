#pragma once
#ifndef _MOTOR_CONTROLLER_H_
#define _MOTOR_CONTROLLER_H_
#include "Packet.h"
#include "utils.h"

class CMotorController
{
  const byte (&m_motorPins)    [4];
  const byte (&m_directionPins)[2];
  
public:
  CMotorController(const byte (&motorPins)[4], const byte (&directionPins)[2])
    : m_motorPins(motorPins)
    , m_directionPins(directionPins)
  {
    stopAll();
  }
  
  void stopAll()
  {
    setAllPins(m_motorPins,     LOW);
    setAllPins(m_directionPins, LOW);
  }

  void apply(const Packet& p)
  {
    if(!p.isValid())
    {
      Serial.print("Invalid packet: ");
      p.dump(Serial);
      return;
    }
    else
    {
      Serial.print("OK: ");
      p.dump(Serial);
    }
      
    const int FR_INDEX = 0;
    const int FL_INDEX = 1;
    const int RR_INDEX = 2;
    const int RL_INDEX = 3;
    
    const int RD_INDEX = 0;
    const int LD_INDEX = 1;
      
    applyDirectionPin(p.m_rightDirection, RD_INDEX);
    applyDirectionPin(p.m_leftDirection,  LD_INDEX);    

    applyMotorPin(p.m_frontRight, FR_INDEX); 
    applyMotorPin(p.m_frontLeft,  FL_INDEX); 
    applyMotorPin(p.m_rearRight,  RR_INDEX); 
    applyMotorPin(p.m_rearLeft,   RL_INDEX); 
  }

private:
  void applyMotorPin(int character, int index)
  {
      const int p = (character - '0') * 255 / 9;
      analogWrite(m_motorPins[index], p);
      Serial1.print(" ** Starting ");  Serial1.print(index); Serial1.print("; power: "); Serial1.println(p, DEC);
  }
  
  void applyDirectionPin(int character, int index)
  {
      int state = character == '1' ? HIGH : LOW;
      digitalWrite(m_directionPins[index], state);
      Serial1.print(" ** Direction ");  Serial1.print(index); Serial1.print("; state: "); Serial1.println(state, DEC);
  }
};

#endif // _MOTOR_CONTROLLER_H_
