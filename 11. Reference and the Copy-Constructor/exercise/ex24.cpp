#include <iostream>
using namespace std;

class X
{
public:
    X() : dx(0) {}
    X(double x) : dx(x) {}
    void print() {cout << "dx = " << dx << endl;}
    double dx;
};

int main()
{
    X x1(1.23);
    X* mptr = &x1;

    double X::*dx = &X::dx;
    void(X::*fptr)() = &X::print;

    x1.print();
    mptr->*dx = 7.89;
    (mptr->*fptr)();
}