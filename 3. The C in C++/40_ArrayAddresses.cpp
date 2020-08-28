// C03: 40_ArrayAddresses.cpp
#include <iostream>
using namespace std;

int main()
{
    int a[10];
    cout << "sizeof(int) = " << sizeof(int) << endl;
    for(int i = 0; i < 10; ++i)
    {
        cout << "&a[" << i << "] = " << &a[i] << endl;
    }
}