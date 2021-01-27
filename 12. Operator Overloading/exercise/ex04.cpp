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
    
    // Ç°×º
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

    // ºó×º
    const IntClass operator++(int)
    {
        IntClass ic(i);
        i++;
        return ic;
    }
    const IntClass operator--(int)
    {
        IntClass ic(i);
        i--;
        return ic;
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
    IntClass a(1), b(2), c(3), d(4);
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;
    cout << "d = " << d << endl;

    cout << "a++ = " << a++ << endl;
    cout << "++b = " << ++b << endl;
    cout << "c-- = " << c-- << endl;
    cout << "--d = " << --d << endl;
}