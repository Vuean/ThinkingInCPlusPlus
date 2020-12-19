#include <iostream>

class X
{
    int a, b;
public:
    X();
    X(int _a, int _b);
    long sum() const;
    long different() const;
    double div() const;
    long mul() const;
    void changesign();
    void print() const;
    int getA() const;
    void setA(int _a);
    int getB() const;
    void setB(int _b);
};

X::X() : a(0), b(1) {}

X::X(int _a, int _b) : a(_a), b(_b) {}

long X::sum() const { return (a + b);}

long X::different() const { return (a - b);}

double X:: div() const
{
    if(b == 0)
        return 0.0;
    else
        return a / b;
}

long X::mul() const
{
    return pow(a, b);
}

void X::changesign()
{
    a *= -1;
    b *= -1;
}

void X::print() const
{
    std::cout << "a = " << a << " b = " << b << std::endl;
}

int X::getA() const
{
    return a;
}

void X::setA(int _a)
{
    a = _a;
}

int X::getB() const
{
    return b;
}

void X::setB(int _b)
{
    b = _b;
}

int main()
{
    X x1();
    const X cx2(10, 2);
    // int x1b = x1.getB();
    int x2v = cx2.getB();
}