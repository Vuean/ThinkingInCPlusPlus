// C14_02_Composition.cpp
// Resue code with coposition
#include "C14_01_Useful.h"
class Y
{
    int i;
public:
    X x;    // embedded object
    Y() { i = 0; }
    void f(int ii) { i = ii; }
    int g() const {return i; } 
};

int main()
{
    Y y;
    y.f(47);
    y.x.set(37);// Access the embedded object
}