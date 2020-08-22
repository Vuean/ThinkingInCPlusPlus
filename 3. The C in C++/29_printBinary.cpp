// C03: 29_printBinary.cpp
#include <iostream>
#include "29_printBinary.h"

void printBinary(const unsigned char val)
{
    for(int i = 7; i >= 0; i--)
    {
        if(val & (1 << 7))
            std::cout << "1";
        else
            std::cout << "0";
    }
}