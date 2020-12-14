#include "Text.h"
#include <iostream>

int main()
{
    Text text("ex01.cpp");
    std::cout << text.contents() << std::endl;
}