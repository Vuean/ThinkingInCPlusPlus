// C11_01_FreeStandingReferences.cpp
#include<iostream>
using namespace std;

// Ordinary free-standing reference:
int y;
int& r = y;

// when a reference is created, it must be initialized to a live object
// However, you can also say:
const int& q = 2;

// References are tied to someone eles's storage:
int x = 0;
int& a = x;

int main()
{
    cout << "x = " << x << ", a = " << a << endl;
    a++;
    cout << "x = " << x << ", a = " << a << endl;
}