#include <iostream>
using namespace std;

typedef struct {
    int i, j, k;
}ThreeDPoint;

int main()
{
    ThreeDPoint p[10];
    for(int i = 0; i < 10; i++)
    {
        p[i].i = i + 1;
        p[i].j = i + 2;
        p[i].k = i + 3;

        cout << "Address p[i].i = " << (long long)&p[i].i << endl;
        cout << "Address p[i].j = " << (long long)&p[i].j << endl;
        cout << "Address p[i].k = " << (long long)&p[i].k << endl;
    }
    cout << "sizeof(struct ThreeDPoint) = " << sizeof(ThreeDPoint) << endl;
}