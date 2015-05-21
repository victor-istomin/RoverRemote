#pragma once

#if defined PERFORM_TESTING   // ---- Unit Tests code, should run on board ----

# include <Arduino.h>
# include "Answer.h"
# include "utils.h"

  inline void testAnswer()
  {
     Serial.print("Test ACK answer... ");
     
     const uint16_t packetId = 0xABCD; 
     Answer ack = Answer::fromAckId(packetId);
     
     Serial.print("sizeof(Answer) = "); Serial.print(sizeof(Answer)); Serial.print("; bytes needed = "); Serial.println(ack.bytesNeeded());
     
     // --- try to write to insufficient buffer ---
     
     char smallBuffer[2] = {0};
     Serial.print(" * smallBufferTest. Written:"); Serial.print(ack.serializeTo(smallBuffer, smallBuffer + sizeof(smallBuffer)), DEC);
     if (smallBuffer[0] == 0)
       Serial.println(" - OK, not changed");
     else
       Serial.println(" - FAIL, should not serialize");
       
     // --- try to write to large enough buffer ---
     
     char enoughBytes[sizeof(packetId) + Answer::OVERHEAD_BYTES] = {0};
     uint8_t written = ack.serializeTo(enoughBytes, enoughBytes + sizeof(enoughBytes));
     Serial.print(" * enough buffer test. Written: "); Serial.print(written, DEC); Serial.print("; dump: "); dumpArray(Serial, enoughBytes);
     if (enoughBytes[0] == 'S' && enoughBytes[1] == 1/*eTYPE_ACK*/ && enoughBytes[2] == 2/*payload size*/ 
      && enoughBytes[3] == 0xAB && enoughBytes[4] == 0xCD && enoughBytes[5] == 'E')
     {
       Serial.println(" - OK");
     }
     else
     {
       Serial.println(" - Fail");
     }
     
     // --- try to write to big buffer ---
     
     char manyBytes[sizeof(enoughBytes) * 2] = {0};
     written = ack.serializeTo(manyBytes, manyBytes + sizeof(manyBytes));
     Serial.print(" * big buffer test. Written: "); Serial.print(written, DEC); Serial.print("; dump: "); dumpArray(Serial, manyBytes);
     if (manyBytes[0] == 'S' && manyBytes[1] == 1/*eTYPE_ACK*/ && manyBytes[2] == 2/*payload size*/ 
      && manyBytes[3] == 0xAB && manyBytes[4] == 0xCD && manyBytes[5] == 'E'
      && manyBytes[6] == 0 && manyBytes[7] == 0 && manyBytes[8] == 0)
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
      
      Serial.println(" * Tests finished");
      while(1); // halt
  }


# define UNIT_TESTS performTests();

#else                  // ---- Unit Tests stub, doing nothing
# define UNIT_TESTS ;
#endif
