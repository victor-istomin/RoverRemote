#include "MotorController.h"

byte MOTOR_PINS[] = {11,10,9,6};
byte DIRECTION_PINS[] = {2,4};

const Packet Packet::nullPacket = Packet();   // TODO - not needed?
int led = 13;

CMotorController* g_controller = NULL;
//SoftwareSerial BtSerial(8, 7); // RX | TX

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
  static Packet lastPacket;
  const  int    maxLoopsWithoutPacket = 2; 
  const  int    loopDelay             = 30;
  static int    loopsWithoutPacket    = maxLoopsWithoutPacket;
 
  skipEndlChars();
  Serial.println(F("enter packet bytes (fr,fl,rr,rl), directions (r,l) and checksum. 7 chars total: "));  
  Serial1.println(F("enter packet bytes (fr,fl,rr,rl), directions (r,l) and checksum. 7 chars total: "));  

  if (Packet::read(Serial, lastPacket) || Packet::read(Serial1, lastPacket))
  {
      g_controller->apply(lastPacket);
      loopsWithoutPacket = 0;
      
      digitalWrite(led, HIGH);
  }
  else
  {
      if (++loopsWithoutPacket > maxLoopsWithoutPacket)
      {
          lastPacket = Packet::nullPacket;
          loopsWithoutPacket = maxLoopsWithoutPacket; // avoid overflow
          g_controller->stopAll();
          
          digitalWrite(led, LOW);
      }
  }
  
  delay(loopDelay); 
}
