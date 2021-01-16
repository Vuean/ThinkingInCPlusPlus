#include <iostream>
using namespace std;

class MyClass
{
public:
    MyClass() {cout << "MyClass::MyClass()" << endl;}
    MyClass(const MyClass&m, int x = 0) {cout << "MyClass::MyClass(const MyClass&, int x = 0)" << endl;}
};

void f(MyClass m){}

int main()
{
    MyClass obj;
    f(obj);
}