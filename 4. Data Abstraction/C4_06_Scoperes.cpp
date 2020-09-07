// C04: C4_06_Scoperes.cpp
// Global scope resolution
#include <iostream>
using namespace std;
int a = 0;

void f() {}

struct S{
    int a = 5;
    void f();
};

void S::f() {
    ::f();  // Would be recursive otherwise!
    ::a++;  // select the global a
    cout << ::a << endl;
    a--;    // The a at struct scope
    cout << a << endl;
}

int main()
{
    S s;
    s.f();
    f();
}