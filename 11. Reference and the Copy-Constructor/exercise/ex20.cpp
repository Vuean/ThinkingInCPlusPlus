#include <iostream>
using namespace std;

class A
{
    int a;
public:
    A() : a(0) {}
    A(int a0) : a(a0) {}
};

A f1()
{
    cout << "f1()" << endl;
    return A();
}

// cannot bind non-const lvalue reference 
// of type 'A&' to an rvalue of type 'A'
// void f2(A& tmp)
void f2(const A& tmp)
{
    cout << "f2()" << endl;
}

int main()
{
    f2(f1());
}
