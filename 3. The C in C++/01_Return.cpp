// C03: Return.cpp
// Use of "return"

#include <iostream>
using namespace std;

char cfunc(int i)
{
    if (0 == i)
    {
        return 'a';
    }
    if(1 == i)
    {
        return 'g';
    }
    if (5 == i)
    {
        return 'z';
    }
    return 'c';    
}

int main()
{
    cout << "type an integer: ";
    int val;
    cin >> val;
    cout << cfunc(val) << endl;
    return 0;
}