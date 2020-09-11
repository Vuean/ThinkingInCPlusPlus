// C05: C5_02_Private.cpp
// Setting the boundary

struct B
{
private:
    char c;
    float f;
public:
    int i;
    void func();
};

void B::func()
{
    i = 0;
    c = 'a';
    f = 1.0;
}

int main()
{
    B b;
    b.i = 1;    // OK, public
    // b.c = 'c';  // Error, private
    // b.f = 3.14;
}