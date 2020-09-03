#include <iostream>
using namespace std;

int main()
{
    double a[10];
    cout << "sizeof(double) = " << sizeof(double) << endl;
    for(int i = 0; i < 10; ++i)
    {
        cout << "&a[" << i << "] = " << (long long)&a[i] << endl;
    }
}