// C8_13_ConstMember.cpp
#include <iostream>
using namespace std;

class X
{
    int i;
public:
    X(int ii);
    int f() const;
};

X::X(int ii) : i(ii) {}

int X::f() const { return i;}

int main()
{
    X x1(10);
    const X x2(20);
    cout << x1.f() << endl;
    cout << x2.f() << endl;
}