// C13_10_PlacementOperatorNew.cpp
// Placement with operator new()
#include <cstddef>
#include <iostream>
using namespace std;

class X
{
    int i;
public:
    X(int ii = 0) : i(ii)
    {
        cout << "this = " << this << endl;
    }
    ~X()
    {
        cout << "X::~X(): " << this << endl;
    }
    void* operator new(size_t, void* loc)
    {
        return loc;
    }
};

int main()
{
    int l[10];
    cout << "l = " << l << endl;
    X* xp = new(l) X(47);   // X at location l
    xp->X::~X();    // Explicit destructor call
}