#pragma once
#ifndef _UTILS_H_
#define _UTILS_H_

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



#endif // _UTILS_H_
