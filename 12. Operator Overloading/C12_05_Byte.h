// C12_05_Byte.h
// Member overloaded operators
#ifndef BYTE_H
#define BYTE_H
#include "../require.h"
#include <iostream>
// Member functions (implicit "this"):
class Byte
{
    unsigned char b;
public:
    Byte(unsigned char bb = 0) : b(bb) {}
    // No side effects: const member functions
    const Byte operator+(const Byte& right) const
    {
        return Byte(b + right.b);
    }
    const Byte operator-(const Byte& right) const
    {
        return Byte(b - right.b);
    }
    const Byte operator*(const Byte& right) const
    {
        return Byte(b * right.b);
    }
    const Byte operator/(const Byte& right) const
    {
        require(right.b != 0), "diveded by zero";
        return Byte(b / right.b);
    }
    const Byte operator%(const Byte& right) const
    {
        require(right.b != 0), "modulo by zero";
        return Byte(b % right.b);
    }
    const Byte operator^(const Byte& right) const
    {
        return Byte(b ^ right.b);
    }
    const Byte operator&(const Byte& right) const
    {
        return Byte(b & right.b);
    }
    const Byte operator|(const Byte& right) const
    {
        return Byte(b | right.b);
    }
    const Byte operator<<(const Byte& right) const
    {
        return Byte(b << right.b);
    }
    const Byte operator>>(const Byte& right) const
    {
        return Byte(b >> right.b);
    }

    // Assignments modify & return lvalue:
    // operator= can only be a member function:
    Byte& operator=(const Byte& right)
    {
        // Handle self-assignment"
        if(this == & right) return *this;
        b = right.b;
        return *this;
    }
    Byte& operator+=(const Byte& right)
    {
        if(this == & right) /*self-assignment*/;
        b += right.b;
        return *this;
    }
    Byte& operator-=(const Byte& right)
    {
        if(this == & right) /*self-assignment*/;
        b -= right.b;
        return *this;
    }
    Byte& operator*=(const Byte& right)
    {
        if(this == & right) /*self-assignment*/;
        b *= right.b;
        return *this;
    }
    Byte& operator/=(const Byte& right)
    {
        require(right.b != 0), "diveded by zero";
        if(this == & right) /*self-assignment*/;
        b /= right.b;
        return *this;
    }
    Byte& operator%=(const Byte& right)
    {
        require(right.b != 0), "modulo by zero";
        if(this == & right) /*self-assignment*/;
        b %= right.b;
        return *this;
    }
    Byte& operator^=(const Byte& right)
    {
        if(this == & right) /*self-assignment*/;
        b ^= right.b;
        return *this;
    }
    Byte& operator&=(const Byte& right)
    {
        if(this == & right) /*self-assignment*/;
        b &= right.b;
        return *this;
    }
    Byte& operator|=(const Byte& right)
    {
        if(this == & right) /*self-assignment*/;
        b |= right.b;
        return *this;
    }
    Byte& operator>>=(const Byte& right)
    {
        if(this == & right) /*self-assignment*/;
        b >>= right.b;
        return *this;
    }
    Byte& operator<<=(const Byte& right)
    {
        if(this == & right) /*self-assignment*/;
        b <<= right.b;
        return *this;
    }
    // Conditional operators return true/false:
    int operator==(const Byte& right) const
    {
        return b == right.b;
    }
    int operator!=(const Byte& right) const
    {
        return b != right.b;
    }
    int operator<(const Byte& right) const
    {
        return b < right.b;
    }
    int operator>(const Byte& right) const
    {
        return b > right.b;
    }
     int operator<=(const Byte& right) const
    {
        return b <= right.b;
    }
    int operator>=(const Byte& right) const
    {
        return b >= right.b;
    }
     int operator&&(const Byte& right) const
    {
        return b && right.b;
    }
    int operator||(const Byte& right) const
    {
        return b || right.b;
    }
    // write the contents to an ostream:
    void print(std::ostream& os) const
    {
        os << "0x" << std::hex << int(b) << std::dec;
    }
};
#endif // BYTE_H