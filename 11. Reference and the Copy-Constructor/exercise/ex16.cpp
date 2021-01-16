#include <iostream>
using namespace std;
class A
{
public:
    A() {cout << "Constructor for Class A" << endl;}
    A(const A& a) { cout << "Copy Constructor for Class A" << endl;}
};

void f1(A a)
{
    cout << "f1(A a) called..." << endl; 
}

A f2()
{
    cout << "f2()  called..." << endl;
    static A tmpa;
    cout << "return A..." << endl;
    return tmpa;
}

int main()
{
    A a;
    f1(a);
    a = f2();
}