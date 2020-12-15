// C08: Safecons.cpp
// Using const of safety
#include <iostream>
using namespace std;

const int i = 100;  // Typical constant
const int j = i + 10; // Value from const expr
long address = (long)&j;    // Force storage
char buf[j + 10];   // Still a const expression

int main()
{
    cout << "type a character & CR: ";
    const char c = cin.get();   // can't change
    const char c2 = c + 'a';
    cout << c2;
}