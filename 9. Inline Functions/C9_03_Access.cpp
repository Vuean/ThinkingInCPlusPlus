// C9_03_Access.cpp
// Inline access funtions
#include <iostream>
class Access
{
    int i;
public:
    int read() const { return i; }
    void set(int ii) { i = ii; }
};

int main()
{
    Access A;
    A.set(100);
    int x = A.read();
    std::cout << x << std::endl;
}