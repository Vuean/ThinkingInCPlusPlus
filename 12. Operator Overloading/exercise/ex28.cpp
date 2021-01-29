#include <iostream>
using namespace std;

class Orange;

class Apple
{
public:
    Apple(Orange& o) {cout << "Apple(Orange)" << endl;}
};

class Orange
{
public:
    Orange() {cout << "Orange" << endl;}
};

void foo(Apple arg) {cout << "foo called()" << endl;}

int main()
{
    Orange b;
    Apple a(b);
    cout << "foo called..." << endl;
    foo(b);
}