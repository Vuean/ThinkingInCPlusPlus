#include <iostream>
using namespace std;

class A
{
    int i;
public:
    A() : i(0) {}
    A(int ii) : i(ii) {}

    const A& operator++()
    {
        i++;
        return *this;
    }
    void print()
    {
        cout << i << endl;
    }
};

int main()
{
    A a;
    ++a;
    a.print();
    // error: no 'operator++(int)' declared for postfix '++'
    // a++;
    // a.print();
}