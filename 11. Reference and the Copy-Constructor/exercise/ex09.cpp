#include <iostream>
using namespace std;

class MyClass
{
public:
    void constFunc() const { cout << "MyClass::constFunc" << endl; }
    void nonconstFunc() { cout << "MyClass::nonconstFunc" << endl; }
};

void f1(MyClass m1)
{
    cout << "f1(MyClass m1)" << endl;
    m1.constFunc();
    m1.nonconstFunc();
    cout << "--------End---------" << endl;
}

void f2(MyClass& m2)
{
    cout << "f2(MyClass& m2)" << endl;
    m2.constFunc();
    m2.nonconstFunc();
    cout << "--------End---------" << endl;
}

void f3(const MyClass& m3)
{
    cout << "fe(const MyClass m3)" << endl;
    m3.constFunc();
    // m3.nonconstFunc();
    cout << "--------End---------" << endl;
}

int main()
{
    MyClass m;
    f1(m);
    f2(m);
    f3(m);
}