// C14_03_Composition2.cpp
// Private embedded objects
#include "C14_01_Useful.h"
class Y
{
    int i;
    X x;    // Embedded object
public:
    Y() { i = 0; }
    void f(int ii) { i = ii; x.set(ii);}
    int g() const {return i * x.read();}
    void permute() {x.permute();}
};

int main()
{
    Y y;
    y.f(47);
    y.permute();
}