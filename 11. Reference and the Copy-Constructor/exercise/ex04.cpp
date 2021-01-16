#include <iostream>
using namespace std;

int& f(int* a)
{
    *a = *a + 1;
    int& b = *a;
    return b;
}

int main()
{
    int a = 10;
    cout << "a = " << a << endl;
    int* ap = &a;
    cout << "f(int* a) = " << f(ap) << endl;
    return 0;
}