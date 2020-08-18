// C03:08_gotoKeyword.cpp
// The infamous goto is supported in C++

#include <iostream>
using namespace std;

int main()
{
    long val;
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 1; j < 100; j += 10)
        {
            val = i * j;
            if(val > 47000)
                goto bottom;
                // Break would only go on the outer 'for'
        }
    }
    bottom:
    cout << val << endl;
    return 0;
}