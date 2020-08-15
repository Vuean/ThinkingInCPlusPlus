/*
C02: Declare.cpp
Declaration & Definition examples
*/

extern int i;   // Declaration without Definition
extern float f(float);  // Function Declaration

float b;    // Declaration & Definition

float f(float a)    // Function Definition
{
    return a + 1.0;
}

int i;  // Definition

int h(int x)    // Declaration & Definition
{
    return x + 1;
}