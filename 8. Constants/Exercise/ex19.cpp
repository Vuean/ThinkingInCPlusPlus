#include <iostream>
using namespace std;

class X
{
    float x;
    const float cfx;
public:
    X();
    ~X();
    void print();
};

X::X() : x(0.1), cfx(0.7f)
{}

X::~X() {}

void X::print()
{
    cout << "x = " << x << endl;
    cout << "cfx = " << cfx << endl;
}
int main()
{
    X fx;
    fx.print();
}