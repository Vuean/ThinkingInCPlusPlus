#include <iostream>
using namespace std;

class MyDouble 
{
    double* dptr;
public:
    MyDouble() : dptr(nullptr) {}
    MyDouble(double d) : dptr(new double (d)) {}

    MyDouble(const MyDouble& x) : dptr(x.dptr) {}

    ~MyDouble() 
    {
        cout << "~MyDouble():" << *dptr << endl;
        //*dptr = -1;
        delete dptr;
        dptr = nullptr;
    }
};

void someFunc(MyDouble x) 
{
    cout << "someFunc() called."<< endl;
}

int main() 
{
    MyDouble obj(1.2);
    someFunc(obj);
    return 0;
}