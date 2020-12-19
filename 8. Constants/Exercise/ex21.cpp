#include <iostream>
class X
{
    const int ivar;
    enum {buf = 10};
    char buffer[buf];
public:
    X();
    ~X();
    void print();
};

X::X() : ivar(0)
{}

X::~X()
{}

void X::print()
{
    std::cout << ivar << std::endl;
    std::cout << "Size: " << sizeof(buffer) / sizeof(char) << std::endl;
}

int main()
{
    X x;
    x.print();
}