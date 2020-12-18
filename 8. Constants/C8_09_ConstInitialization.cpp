// C8_09_ConstInitialization.cpp
// Initializing const in classes
#include <iostream>
using namespace std;

class Fred
{
    const int size;
public:
    Fred(int sz);
    void print();
};

Fred::Fred(int sz)
    : size(sz)
{}

void Fred::print()
{
    cout << size << endl;
}

int main()
{
    Fred a(1), b(2), c(3);
    a.print(); b.print(); c.print();
}

