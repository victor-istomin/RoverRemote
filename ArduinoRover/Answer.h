#pragma once
#include <cstdint>
#include "utils.h"

class Answer
{
public:
  static Answer fromAckId       (uint16_t packetId)     { return Answer(packetId,     Tag<DataType, eTYPE_ACK>());     }
  static Answer fromBatteryState(uint8_t  batteryState) { return Answer(batteryState, Tag<DataType, eTYPE_BATTERY>()); }
  
  bool serializeTo(char* buffer, size_t bufferSize)
  {
    return false; // todo
  }

private:
  static const char START_SIGNATURE = 'S'; 
  static const char END_SIGNATURE   = 'E'; 
  
  //! available data types
  enum DataType : uint8_t 
  {
    eTYPE_NONE = 0,
    eTYPE_ACK,        //!< command accepted
    eTYPE_BATTERY,    //!< battery state
    
    eTYPES_COUNT      //!< not a type
  };
  
  //! access the data in buffer
  union Data
  {
    uint16_t m_ackPacketId;
    uint8_t  m_batteryState;  //!< battery state in 1/256 of max voltage
  }
  
  static const uint8_t SIZES[eTYPES_COUNT] = {0, sizeof(Data::m_ackPacketId), sizeof(Data::m_batteryState) };

  // --- answer packet data section
  uint8_t m_size;       //!< payload size without start/end signatures
  Data    m_data;       //!< payload
  // --- answer packet data section end

  Answer(uint16_t batteryState, Tag<DataType, eTYPE_ACK> tag)
    : m_size(SIZES[tag::value])
  {
    m_data.m_ackPacketId = ackPacketId;
  }
  
  Answer(uint8_t ackPacketId, Tag<DataType, eTYPE_BATTERY> tag)
    : m_size(SIZES[tag::value])
  {
    m_data.m_batteryState = batteryState;
  }
};
