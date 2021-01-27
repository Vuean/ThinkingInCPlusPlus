#include <iostream>
using namespace std;

class IntClass
{
    int i;
public:
    IntClass() : i(0) {}
    IntClass(int ii) : i(ii) {}
    const IntClass operator+(const IntClass& right) const 
    {
        return IntClass(i + right.i);
    }
    const IntClass operator-(const IntClass& right) const
    {
        return IntClass(i - right.i);
    }
    void print(ostream& out)
    {
        out << i << endl;
    }
};

int main()
{
    IntClass a(1), b(9), c(5);
    IntClass d = a + b - c;
    d.print(cout);
}