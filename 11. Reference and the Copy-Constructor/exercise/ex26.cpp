#include <iostream>
using namespace std;
class Simple2 
{
public:
    int f(float) const { return 1; }
    void f(char c) const {cout << c << endl;}
};

int(Simple2::*ffp)(float) const;
int(Simple2::*ffp2)(float) const = &Simple2::f;

void(Simple2::*fcp)(char) const = &Simple2::f;

int main()
{
    ffp = &Simple2::f;

    Simple2 s;
    Simple2* sptr = &s;
    (sptr->*ffp2)(1.2);
    (sptr->*fcp)('z');
}