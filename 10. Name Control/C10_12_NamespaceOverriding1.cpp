// C10_12_NamespaceOverriding1.cpp
#include "C10_10_NameSpaceMath.h"
int main()
{
    using namespace Math;
    Integer a;  // Hide Math::a
    a.setSign(negative);
    // Now scope resolution is necessary to select Math::a
    Math::a.setSign(positive);
}