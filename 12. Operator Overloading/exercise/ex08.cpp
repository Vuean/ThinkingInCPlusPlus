#include <iostream>
using namespace std;

class IntClass
{
    int i;
    friend ostream& operator<<(ostream& out, const IntClass& is);
public:
    IntClass() : i(0) {}
    IntClass(int ii) : i(ii) {}
    const IntClass operator+(const IntClass& right) const 
    {
        return IntClass(i + right.i);
    }
    const IntClass operator-() const {return IntClass(-i);}
    void print(ostream& out)
    {
        out << i << endl;
    }
};

ostream& operator<<(ostream& out, const IntClass& is)
{
    out << is.i;
    return out;
}

int main()
{
    IntClass a(1), b(9);
    IntClass c = a + b;
    cout << -c << endl;
}