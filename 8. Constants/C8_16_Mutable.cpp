// C8_16_Mutable.cpp
// The mutable keyword
#include <iostream>
class Z
{
    int i;
    mutable int j;
public:
    Z();
    void print() const;
    void f() const;
};

Z::Z() : i(0), j(0) {}

void Z::f() const
{
    // i++;     // Error -- const member function
    j++;
}

void Z::print() const
{
    std::cout << i << " " << j << std::endl;
}

int main()
{
    const Z zz;
    zz.f();
    zz.print();
}