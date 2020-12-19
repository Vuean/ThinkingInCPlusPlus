#include "ex07_0.h"
#include <iostream>

int current_time = 1219;

void print()
{
    current_time = 1220;
    std::cout << "current time is: " << current_time << std::endl;
}