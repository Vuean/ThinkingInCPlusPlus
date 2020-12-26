// C10_15_UsingDeclaration2.cpp
#include "C10_14_UsingDeclaration.h"
namespace Q
{
    using U::f;
    using V::g;
}

void m()
{
    using namespace Q;
    f();    // Calls U::f()
    g();    // Calls V::g()
}
int main() {}