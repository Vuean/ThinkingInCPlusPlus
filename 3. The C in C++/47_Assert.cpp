// C03:47_Assert.cpp
// Use of the assert() debugging macro

#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    int i = 100;
    assert(i != 100);   // Fails
}