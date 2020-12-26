// C10_13_OverridingAmbiguity.cpp
#include "C10_10_NameSpaceMath.h"
#include "C10_12_NamespaceOverriding2.h"
void s()
{
    using namespace Math;
    using namespace Calculation;
    // Everything is OK until
    divide(1, 2);   // Ambiguity
}
int main() { }