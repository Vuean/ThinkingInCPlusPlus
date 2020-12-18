// C8_10_BuiltInTypeConstructors.cpp
#include <iostream>
using namespace std;

class B
{
    int i;
public:
    B(int i);
    void print();
};

B::B(int ii)
    : i(ii) {}

void B::print()
{
    cout << i << endl;
}

int main()
{
    B a(1), b(2);
    float pi(3.1415926);
    a.print();b.print();
    cout << pi << endl;
}