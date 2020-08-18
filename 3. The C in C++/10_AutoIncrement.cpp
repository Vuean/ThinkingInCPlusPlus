// C03:10_AutoIncrement.cpp
// Shows use of auto-increment and auto-decrement operators

#include <iostream>
using namespace std;

int main()
{
    int i = 0;
    int j = 0;
    cout << "++i-> " << ++i << endl;  // Pre-increment
    cout << "j++-> " << j++ << endl;  // Post-increment
    cout << "--i-> " << --i << endl;   // Pre-decrement
    cout << "j---> " << j-- << endl;   // Post-decrement
    return 0;
}