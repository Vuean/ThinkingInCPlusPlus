// C05: C5_01_Public.cpp
// Public is just like C's struct

struct A
{
    int i;
    char c;
    float f;
    void func();
};
void A::func() {}

struct B
{
public:
    int i;
    char c;
    float f;
    void func();
};
void B::func() {}

int main()
{
    A a; B b;
    a.i = b.i = 1;
    a.c = b.c = 'c';
    a.f = b.f = 1.0;
    a.func();
    b.func();
}