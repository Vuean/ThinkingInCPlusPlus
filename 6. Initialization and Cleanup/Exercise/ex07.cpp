#include <iostream>
using namespace std;

int main()
{
    double d1[3] = {1.1, 2.2};
    for(int i = 0; i < (sizeof(d1) / sizeof(*d1)); i++)
    {
        cout << d1[i] << " ";
    }
    cout << endl;

    double d2[] = {9.9, 8.8, 7.7, 6.6};
    for(int i = 0; i < (sizeof(d2) / sizeof(*d2)); i++)
    {
        cout << d2[i] << " ";
    }
    cout << endl;
}