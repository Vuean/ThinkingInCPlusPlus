// C9_06_Cpptime.cpp
#include "C9_06_Cpptime.h"
#include <iostream>
using namespace std;

int main()
{
    Time start;
    for(int i = 0; i < 1000; i++)
    {
        cout << i << ' ';
        if(i%10 == 0)
            cout << endl;
    }
    Time end;
    cout << endl;
    cout << "start = " << start.ascii();
    cout << "end = " << end.ascii();
    cout << "delta = " << end.delta(&start);
}