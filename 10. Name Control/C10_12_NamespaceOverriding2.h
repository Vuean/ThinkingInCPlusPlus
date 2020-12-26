// C10_12_NamespaceOverriding2.h
#ifndef NAMESPACEOVERRING2_H
#define NAMESPACEOVERRING2_H
#include "C10_10_NameSpaceMath.h"
namespace Calculation
{
    using namespace Int;
    Integer divide(Integer, Integer);
}
#endif // NAMESPACEOVERRING2_H