#include <iostream>

void print(float value)
{
    const float& another_value = value;
    // another_value = 20;
    std::cout << "value: " << value << std::endl;
}

int main()
{
    print(3.3);
}