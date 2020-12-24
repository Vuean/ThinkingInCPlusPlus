#include <iostream>
using namespace std;

#define INT_FIELD(a) int_##a
#define FIELD(a) static int int_##a = a

FIELD(1); FIELD(2);
FIELD(3); FIELD(0);

void showVarAt(int index)
{
    switch (index)
    {
        case 1: cout << INT_FIELD(1) << endl; break;
        case 2: cout << INT_FIELD(2) << endl; break;
        case 3: cout << INT_FIELD(3) << endl; break;
        default: cout << INT_FIELD(0) << endl; break;
    }
}

int main()
{
    for(int i = 0; i < 10; ++i)
        showVarAt(i);
}