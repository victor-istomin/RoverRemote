#include "MotorController.h"

byte MOTOR_PINS[] = {11,10,9,6};
byte DIRECTION_PINS[] = {2,4};

int led = 13;

CMotorController* g_controller = NULL;

void skipEndlChars()
{
    char c = Serial.peek();
    while(c == '\n' && c == '\r')
    {
      Serial.read();
      c = Serial.peek();
    }
}

// the setup routine runs once when you press reset:
void setup() 
{
  static CMotorController controller = CMotorController(MOTOR_PINS, DIRECTION_PINS);
  g_controller = &controller;

  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  digitalWrite(13, HIGH);

  // initialize serial:
  Serial.begin(38400);
  Serial1.begin(38400);

  digitalWrite(13, HIGH);
  Serial.println("Init...");
  delay(1000);
  
}

// the loop routine runs over and over again forever:
void loop() 
{
  const  int    loopDelay             = 20;
  const  int    maxPacketLeaseTime    = 500;  // time before last move command will be forcibly discarded
  const  int    maxLoopsWithoutPacket = maxPacketLeaseTime / loopDelay;
  static int    loopsWithoutPacket    = maxLoopsWithoutPacket;
 
  // Waiting 7 packet bytes: (fr,fl,rr,rl), directions (r,l) and checksum.
  skipEndlChars();

  Packet packet;
  if (Packet::read(Serial, packet) || Packet::read(Serial1, packet))
  {
      g_controller->apply(packet);
      loopsWithoutPacket = 0;
      
      digitalWrite(led, HIGH);
  }
  else
  {
      if (++loopsWithoutPacket > maxLoopsWithoutPacket)
      {
          loopsWithoutPacket = maxLoopsWithoutPacket; // avoid overflow
          g_controller->stopAll();
          
          digitalWrite(led, LOW);
      }
  }
  
  delay(loopDelay); 
}
