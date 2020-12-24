#include <iostream>
using namespace std;

class A
{
public:
    A() {cout << "A::A()" << endl;}
};

class B
{
    A a;
public:
    B() {cout << "B::B()" << endl;}
};

int main()
{
    B b[10];
}