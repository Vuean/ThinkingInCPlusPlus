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
    int x;
    A a;
public:
    B(int x0 = 1) : x(x0), a() {}
    void print() {cout << "x = " << x << endl;}
};

int main()
{
    cout << "Creating first object" << endl;
    B obj1(111);
    cout << "Assignment operator calls copy constructor" << endl;
    B obj2 = obj1;

    obj1.print();
    obj2.print();
}