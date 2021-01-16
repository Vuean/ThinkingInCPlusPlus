#include <iostream>
using namespace std;
class A
{
public:
    A() {cout << "Constructor for Class A" << endl;}
    A(const A& a) { cout << "Copy Constructor for Class A" << endl;}
};

class B
{
    A a;
};

void f(B b) {}

int main()
{
    B b;
    f(b);
}