// C14_04_Inheritance.cpp
#include "C14_01_Useful.h"
#include <iostream>
using namespace std;

class Y : public X
{
    int i;  // Different from X's i
public:
    Y() {i = 0;}
    int change()
    {
        i = permute();  // Different name call
        return i;
    }
    void set(int ii)
    {
        i = ii;
        X::set(ii);
    }
};

int main()
{
    cout << "sizeof(X) = " << sizeof(X) << endl;
    cout << "sizeof(Y) = " << sizeof(Y) << endl;
    Y D;
    D.change();
    // X function interface comes through:
    D.read();
    D.permute();
    // Redefined functions hide base versions:
    D.set(12) ;
}
