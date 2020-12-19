#include <iostream>

int main()
{
    const char hello[] = {'c', 'o', 'n', 's', 't', '\0'};
    // hello[0] = 'n';  // 必须是可修改的左值
    // *hello = 'n';
    std::cout << hello << std::endl;
}