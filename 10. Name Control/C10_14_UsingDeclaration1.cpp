// C10_14_UsingDeclaration1.cpp
#include "C10_14_UsingDeclaration.h"
void h()
{
    using namespace U;  // Using directive
    using V::f;   // Using declaration
    f();    // Calls V::f();
    U::f(); // Must fully quality to call
}