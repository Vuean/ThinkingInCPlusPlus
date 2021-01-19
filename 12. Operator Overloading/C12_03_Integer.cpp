// C12_03_Integer.cpp
// Implementation of overloaded operators
#include "C12_03_Integer.h"
#include "..\require.h"

const Integer operator+(const Integer& left, const Integer& right)
{
    return Integer(left.i + right.i);
}

const Integer operator-(const Integer& left, const Integer& right)
{
    return Integer(left.i - right.i);
}

const Integer operator*(const Integer& left, const Integer& right)
{
    return Integer(left.i * right.i);
}

const Integer operator/(const Integer& left, const Integer& right)
{
    require(right.i != 0, "divide by zero");
    return Integer(left.i / right.i);
}

const Integer operator%(const Integer& left, const Integer& right)
{
    require(right.i != 0, "dodulo by zero");
    return Integer(left.i % right.i);
}

const Integer operator^(const Integer& left, const Integer& right)
{
    return Integer(left.i ^ right.i);
}

const Integer operator&(const Integer& left, const Integer& right)
{
    return Integer(left.i & right.i);
}

const Integer operator|(const Integer& left, const Integer& right)
{
    return Integer(left.i | right.i);
}

const Integer operator<<(const Integer& left, const Integer& right)
{
    return Integer(left.i << right.i);
}

const Integer operator>>(const Integer& left, const Integer& right)
{
    return Integer(left.i >> right.i);
}

// Assignments modify & return lvalue:
Integer& operator+=(Integer& left, const Integer& right)
{
    if(&left == &right){/*self-assignment*/}
    left.i += right.i;
    return left;
}

Integer& operator-=(Integer& left, const Integer& right)
{
    if(&left == &right){/*self-assignment*/}
    left.i -= right.i;
    return left;
}

Integer& operator*=(Integer& left, const Integer& right)
{
    if(&left == &right){/*self-assignment*/}
    left.i *= right.i;
    return left;
}

Integer& operator/=(Integer& left, const Integer& right)
{
    require(right.i != 0, "divide by zero");
    if(&left == &right){/*self-assignment*/}
    left.i /= right.i;
    return left;
}

Integer& operator%=(Integer& left, const Integer& right)
{
    require(right.i != 0, "modulo by zero");
    if(&left == &right){/*self-assignment*/}
    left.i %= right.i;
    return left;
}

Integer& operator^=(Integer& left, const Integer& right)
{
    if(&left == &right){/*self-assignment*/}
    left.i ^= right.i;
    return left;
}

Integer& operator&=(Integer& left, const Integer& right)
{
    if(&left == &right){/*self-assignment*/}
    left.i &= right.i;
    return left;
}

Integer& operator|=(Integer& left, const Integer& right)
{
    if(&left == &right){/*self-assignment*/}
    left.i |= right.i;
    return left;
}

Integer& operator>>=(Integer& left, const Integer& right)
{
    if(&left == &right){/*self-assignment*/}
    left.i >>= right.i;
    return left;
}

Integer& operator<<=(Integer& left, const Integer& right)
{
    if(&left == &right){/*self-assignment*/}
    left.i <<= right.i;
    return left;
}

// Conditional operators return true/false:
int operator==(const Integer& left, const Integer& right)
{
    return left.i == right.i;
}

int operator!=(const Integer& left, const Integer& right)
{
    return left.i != right.i;
}

int operator>(const Integer& left, const Integer& right)
{
    return left.i > right.i;
}

int operator<(const Integer& left, const Integer& right)
{
    return left.i < right.i;
}

int operator>=(const Integer& left, const Integer& right)
{
    return left.i >= right.i;
}

int operator<=(const Integer& left, const Integer& right)
{
    return left.i <= right.i;
}

int operator&&(const Integer& left, const Integer& right)
{
    return left.i && right.i;
}

int operator||(const Integer& left, const Integer& right)
{
    return left.i || right.i;
}