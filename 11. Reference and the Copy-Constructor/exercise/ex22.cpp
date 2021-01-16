#include <iostream>
using namespace std;

class X
{
    int x;
    X(const X& tmp) : x(0) {}
public:
    X() : x(0) {}
    void add() {x++;}
    X* clone() const;
};

X* X::clone() const
{
    X* ptr = new X();
    ptr->x = x;
    return ptr;
}

void modifyX(const X& tmp)
{
    X* tmpx = tmp.clone();
    tmpx->add();
    delete tmpx;
}

int main()
{
    X x;
    modifyX(x);
}