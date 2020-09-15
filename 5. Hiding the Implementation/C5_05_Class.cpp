// C05: C5_05_Class.cpp
// Similarity of struct and class

struct A
{
private:
    int i, j, k;
public:
    int f();
    void g();
};

int A::f()
{
    return i + j + k;
}

void A::g()
{
    i = j = k = 0;
}

// Identical results are produced with:

class B
{
    int i, j, k;
public:
    int f();
    void g();
};

int B::f()
{
    return i + j + k;
}

void B::g()
{
    i = j = k = 0;
}

int main()
{
    A a;
    B b;
    a.f(); a.g();
    b.f(); b.g();
}