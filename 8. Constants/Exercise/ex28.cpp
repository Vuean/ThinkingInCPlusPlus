#include <iostream>

class bird
{
public:
    void fly();
};

class rock
{};

void bird::fly()
{
    std::cout << "Flying..." << std::endl;
}

int main()
{
    rock r;
    bird* b;
    void* tmp = (void*)&r;
    b = (bird*)tmp;
    b->fly();
}