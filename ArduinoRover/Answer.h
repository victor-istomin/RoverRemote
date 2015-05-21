#pragma once
#include <stdint.h>
#include "utils.h"

class Answer
{
private:

  union Data
  {
    uint16_t m_ackPacketId;
    uint8_t  m_batteryState;  //!< battery state in 1/256 of max voltage
  };
  
  //! available data types
  enum DataType : uint8_t 
  {
    eTYPE_NONE = 0,
    eTYPE_ACK,        //!< command accepted
    eTYPE_BATTERY,    //!< battery state
    
    eTYPES_COUNT      //!< not a type
  };


  // --- answer packet data section
  DataType m_type;
  uint8_t  m_size;       //!< payload size without start/end signatures
  Data     m_data;       //!< payload
  // --- answer packet data section end

  Answer(uint16_t ackPacketId, Tag<DataType, eTYPE_ACK> tag)
    : m_size(SIZES[eTYPE_ACK])
  {
    m_data.m_ackPacketId = ackPacketId;
  }
  
  Answer(uint8_t batteryState, Tag<DataType, eTYPE_BATTERY> tag)
    : m_size(SIZES[eTYPE_BATTERY])
  {
    m_data.m_batteryState = batteryState;
  }

public:
  // use static methonds instead of contructors
  static Answer fromAckId       (uint16_t packetId)     { return Answer(packetId,     Tag<DataType, eTYPE_ACK>());     }
  static Answer fromBatteryState(uint8_t  batteryState) { return Answer(batteryState, Tag<DataType, eTYPE_BATTERY>()); }
  
  static const char   START_SIGNATURE = 'S'; 
  static const char   END_SIGNATURE   = 'E'; 
  static const size_t OVERHEAD_BYTES = sizeof(START_SIGNATURE) + sizeof(END_SIGNATURE) + sizeof(m_size) + sizeof(m_type) ;
  uint8_t bytesNeeded() const                           { return m_size + OVERHEAD_BYTES; }
  
  // serialize answer packet to buffer, return number of bytes added
  int serializeTo(char* bufferStart, const char* bufferEnd) const
  {
    static_assert(sizeof(*this) == 4, "Check struct alignment and size"); // just for invalid compiler switches detection. Change this when struct size changed  
    
    if ((bufferEnd - bufferStart) < bytesNeeded())
    { 
      return 0;
    }
    
    uint8_t* currentByteOut = (uint8_t*)bufferStart;
    
    *currentByteOut     = START_SIGNATURE;
    *(++currentByteOut) = m_type;          // actually, *p++, *(p++), *(++p) are the same. This one is just more straighforward
    *(++currentByteOut) = m_size;
    
    for(uint8_t* data = (uint8_t*)&m_data; data != m_size + (uint8_t*)&m_data; ++data)
      *(++currentByteOut) = *data;
      
    *(++currentByteOut) = END_SIGNATURE;
    
    return currentByteOut - (uint8_t*)bufferStart;
  }
  
  static constexpr uint8_t SIZES[eTYPES_COUNT] = {0, sizeof(Data::m_ackPacketId), sizeof(Data::m_batteryState) };
};
