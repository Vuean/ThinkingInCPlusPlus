// C11_11_SimpleStructure.cpp
struct Simple {int a;};

int main()
{
    Simple so, *sp = &so;
    sp->a;
    so.a;
}