#include <iostream>
using namespace std;

class X
{
public:
    inline void f1()
    {
        f2();
        cout << "f1() call f2()" << endl;
    }
    inline void f2()
    {
        cout << "f2() call " << endl;
    }
};

int main()
{
    X x1;
    x1.f1();
}