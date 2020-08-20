// C03:24_Static.cpp
// Using a static variable in a function

#include <iostream>
using namespace std;

void func()
{
    static int i = 0;
    cout << "i = " << ++i << endl;
}

int main()
{
    for(int x = 0; x < 10; ++x)
        func();
    return 0;
}