#include <iostream>
using namespace std;

class IntClass
{
    int i;
    friend ostream& operator<<(ostream& out, const IntClass& ic);
public:
    IntClass() : i(0) {}
    IntClass(int ii) : i(ii) {}
    const IntClass operator+(const IntClass& right) const 
    {
        return IntClass(i + right.i);
    }
    
    // ǰ׺
    const IntClass& operator++()
    {
        i++;
        return *this;
    }
    const IntClass& operator--()
    {
        i--;
        return *this;
    }

    void print(ostream& out)
    {
        out << i << endl;
    }
};

ostream& operator<<(ostream& out, const IntClass& ic)
{
    out << ic.i;
    return out;
}

int main()
{
    IntClass a;
    a++;
    cout << a << endl;
    a--;
    cout << a << endl;
}