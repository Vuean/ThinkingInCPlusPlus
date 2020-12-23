#include <iostream>
#define FLOOR(x, b) (x>=b?0:1)

int main()
{
    int a = 7;
    if(FLOOR(a&0x0f, 0x07))
        std::cout << "TRUE" << std::endl;
    else
        std::cout << "FALSE" << std::endl;
}