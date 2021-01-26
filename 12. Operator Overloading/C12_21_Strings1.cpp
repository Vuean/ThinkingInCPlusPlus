// C12_21_Strings1.cpp
// No auto tupe conversion
#include "../require.h"
#include <cstring>
#include <cstdlib>
#include <string>
using namespace std;

class Stringc
{
    string s;
public:
    Stringc(const string& str = "") : s(str) {}
    int strcmp(const Stringc& S) const
    {
        return ::strcmp(s.c_str(), S.s.c_str());
    }
};

int main()
{
    Stringc s1("hello"), s2("there");
    s1.strcmp(s2);
}