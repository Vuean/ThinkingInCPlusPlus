#include <iostream>
using  namespace std;

class A
{
    int a;
public:
    A(int value);
    void setA(int value);
    void print();
};

A::A(int value)
{
    a = value;
}

void A::setA(int value)
{
    a = value;
}

void A::print()
{
    cout << "The value is: " << a << endl;
}

int main()
{
    // 此时，若写A a;则会报错，没有默认构造函数
    A a(0);
    a.setA(5);
    a.print();
}