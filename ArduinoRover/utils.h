#pragma once
#ifndef _UTILS_H_
#define _UTILS_H_
#include <Arduino.h>

#define countof(x) (sizeof(x)/sizeof(*x))

template <size_t Size>
void setAllPins(const byte (&pins)[Size], int newState)
{
    for(const byte* pPin = &pins[0]; pPin < &pins[Size]; ++pPin)
    {
        pinMode(*pPin, OUTPUT);
        digitalWrite(*pPin, newState);
    }
}

// this is a helper tag structure for overloading functions "by enum value"
template <typename Enum, Enum Value>
struct Tag
{
    static const Enum value = Value;
};

template <typename Int, size_t N>
void dumpArray(Stream& s, Int (&array)[N])
{
    s.print('{');
    for (int i=0; i<N; ++i)
    {
      if (i > 0)
        s.print(',');
      s.print(array[i], HEX);
    }
    s.print('}');
}


#endif // _UTILS_H_
