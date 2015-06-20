#pragma once

#if defined PERFORM_TESTING   // ---- Unit Tests code, should run on board ----

# include <Arduino.h>
# include "Answer.h"
# include "utils.h"

  inline void testAnswer()
  {
     Serial.print("Test ACK answer... ");
     
     const uint16_t packetId = 0xBEEF; 
     Answer ack = Answer::fromAckId(packetId);
     
     Serial.print("sizeof(Answer) = "); Serial.print(sizeof(Answer)); Serial.print("; bytes needed = "); Serial.println(ack.bytesNeeded());
     
     // --- try to write to insufficient buffer ---
     
     uint8_t smallBuffer[2] = {0};
     Serial.print(" * smallBufferTest. Written:"); Serial.print(ack.serializeTo(smallBuffer, smallBuffer + sizeof(smallBuffer)), DEC);
     if (smallBuffer[0] == 0)
       Serial.println(" - OK, not changed");
     else
       Serial.println(" - FAIL, should not serialize");
       
     // --- try to write to large enough buffer ---
     
     uint8_t enoughBytes[sizeof(packetId) + Answer::OVERHEAD_BYTES] = {0};
     uint8_t written = ack.serializeTo(enoughBytes, enoughBytes + sizeof(enoughBytes));
     Serial.print(" * enough buffer test. Written: "); Serial.print(written, DEC); Serial.print("; dump: "); dumpArray(Serial, enoughBytes);
     if (enoughBytes[0] == 'S' && enoughBytes[1] == 1/*eTYPE_ACK*/ && enoughBytes[2] == 2/*payload size*/ 
      && enoughBytes[3] == 0xEF && enoughBytes[4] == 0xBE && enoughBytes[5] == 'E')
     {
       Serial.println(" - OK");       
     }
     else
     {
       Serial.println(" - Fail");
     }
     
     // --- try to write to big buffer ---
     
     uint8_t manyBytes[sizeof(enoughBytes) * 2] = {0};
     written = ack.serializeTo(manyBytes, manyBytes + sizeof(manyBytes));
     Serial.print(" * big buffer test. Written: "); Serial.print(written, DEC); Serial.print("; dump: "); dumpArray(Serial, manyBytes);
     if (manyBytes[0] == 'S'  && manyBytes[1] == 1/*eTYPE_ACK*/ && manyBytes[2] == 2/*payload size*/ 
      && manyBytes[3] == 0xEF && manyBytes[4] == 0xBE   // little-endian
      && manyBytes[5] == 'E'  && manyBytes[6] == 0 && manyBytes[7] == 0 && manyBytes[8] == 0)
     {
       Serial.println(" - OK");
     }
     else
     {
       Serial.println(" - Fail");
     }
  }
  
  inline void testBatteryState()
  {
     Serial.println("Test battery packet...");
    
     const uint8_t batteryState = 0x12;
     Answer ans = Answer::fromBatteryState(batteryState);
    
     uint8_t smallBuffer[2] = {0};
     Serial.print(" * smallBufferTest. Written:"); Serial.print(ans.serializeTo(smallBuffer, smallBuffer + sizeof(smallBuffer)), DEC);
     if (smallBuffer[0] == 0)
       Serial.println(" - OK, not changed");
     else
       Serial.println(" - FAIL, should not serialize");
       
     // --- try to write to large enough buffer ---
     
     uint8_t enoughBytes[sizeof(batteryState) + Answer::OVERHEAD_BYTES] = {0};
     uint8_t written = ans.serializeTo(enoughBytes, enoughBytes + sizeof(enoughBytes));
     Serial.print(" * enough buffer test. Written: "); Serial.print(written, DEC); Serial.print("; dump: "); dumpArray(Serial, enoughBytes);
     if (enoughBytes[0] == 'S' && enoughBytes[1] == 2/*eTYPE_BATTERY*/ && enoughBytes[2] == 1/*payload size*/ 
      && enoughBytes[3] == batteryState && enoughBytes[4] == 'E')
     {
       Serial.println(" - OK");       
     }
     else
     {
       Serial.println(" - Fail");
     }
     
     // --- try to write to big buffer ---
     
     uint8_t manyBytes[sizeof(enoughBytes) * 2] = {0};
     written = ans.serializeTo(manyBytes, manyBytes + sizeof(manyBytes));
     Serial.print(" * big buffer test. Written: "); Serial.print(written, DEC); Serial.print("; dump: "); dumpArray(Serial, manyBytes);
     if (manyBytes[0] == 'S'  && manyBytes[1] == 2/*eTYPE_BATTERY*/ && manyBytes[2] == 1/*payload size*/ 
      && manyBytes[3] == batteryState
      && manyBytes[4] == 'E'  && manyBytes[5] == 0 && manyBytes[6] == 0 && manyBytes[7] == 0)
     {
       Serial.println(" - OK");
     }
     else
     {
       Serial.println(" - Fail");
     }
    
  }

  inline void performTests()
  {
      while(!Serial) ;
      
      testAnswer();
      testBatteryState();
      
      Serial.println(" * Tests finished");
      while(1); // halt
  }


# define UNIT_TESTS performTests();

#else                  // ---- Unit Tests stub, doing nothing
# define UNIT_TESTS ;
#endif
