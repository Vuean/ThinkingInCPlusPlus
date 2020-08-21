// C03: 26_Forward.cpp
// Forward function & data declarations

#include <iostream>
using namespace std;

// This is not actually external, but the compiler must be told it exists somewhere
extern int i;
extern void func();

int main()
{
    i = 0;
    func();
}

int i;  // The data Definition
void func()
{
    i++;
    cout << i;
}