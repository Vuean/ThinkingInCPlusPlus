#include <iostream>
using namespace std;

int main()
{
    long a[10];
    long *ipa = a;
    for(int i = 0; i < 10; ++i)
        ipa[i] = i * 10;
    
    long double b[10];
    long double *ipb = b;
    for(int i = 0; i < 10; ++i)
        ipb[i] = i * 10;
}