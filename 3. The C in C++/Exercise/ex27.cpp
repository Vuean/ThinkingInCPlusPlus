#include <iostream>
using namespace std;

int main()
{
    const int size = 5;
    const double d1[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    volatile double d2[] = {10.1, 20.1, 30.1, 40.1, 50.1};

    for (int i = 0; i < size; i++)
    {
        double *d = const_cast<double*>(&d1[i]);
        *d *= i;
        d = const_cast<double*>(&d2[i]);
        *d += i; 
    }

    cout << "After change array d1: " << endl;
    for (int i = 0; i < size; i++)
    {
        cout << d1[i] << ", " << endl;
    }

    cout << "After change array d2: " << endl;
    for (int i = 0; i < size; i++)
    {
        cout << d2[i] << ", " << endl;
    }

    return 0;
}