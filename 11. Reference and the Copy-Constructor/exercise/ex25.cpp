#include <iostream>
using namespace std;
class X
{
public:
    X() : x_array{1, 2, 3, 4, 5} {}
    int x_array[5];
};

int main()
{
    X x;
    X* xptr = &x;
    int(X::*x_arrayptr)[5] = &X::x_array;
    cout << *(xptr->*x_arrayptr + 2) << endl;
}