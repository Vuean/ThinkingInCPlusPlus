// C05: C5_03_Friend.cpp
// Friend allows special access

// Declaration (incomplete type specification):
# include <iostream>
using namespace std;
struct X;

struct Y{
    void f(X*);
};

struct X{
private:
    int i;
public:
    void initialize();
    friend void g(X*, int); // Global friend
    friend void Y::f(X*);   // struct member friend
    friend struct Z;        // Entire struct os a friend
    friend void h();          
};

void X::initialize()
{
    i = 0;
}

void g(X* x, int i)
{
    x->i = i;
}

void Y::f(X* x)
{
    x->i = 47;
}

struct Z{
private:
    int j;
public:
    void initialize();
    void g(X* x);
};

void Z::initialize()
{
    j = 99;
}

void Z::g(X* x)
{
    x->i += j;
    cout << x->i;
}

void h()
{
    X x;
    x.i = 100;  // Direct data manipulation
}

int main()
{
    X x;
    x.initialize();
    Z z;
    z.initialize();
    z.g(&x);
}
