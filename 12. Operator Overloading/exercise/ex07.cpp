#include <iostream>
using namespace std;

class IntClass
{
    int i;
public:
    IntClass() : i(0) {}
    IntClass(int ii) : i(ii) {}
    
    friend const IntClass operator+(const IntClass& left, const IntClass& right);
    friend const IntClass operator-(const IntClass& left, const IntClass& right);

    void print(ostream& out)
    {
        out << i << endl;
    }
};

const IntClass operator+(const IntClass& left, const IntClass& right)
{
    return IntClass(left.i + right.i);
}
const IntClass operator-(const IntClass& left, const IntClass& right)
{
    return IntClass(left.i - right.i);
}

int main()
{
    IntClass a(1), b(9), c(5);
    IntClass d = a + b - c;
    d.print(cout);
}