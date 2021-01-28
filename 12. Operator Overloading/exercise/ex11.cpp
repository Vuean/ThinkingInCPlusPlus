#include <iostream>
using namespace std;
class Number
{
    double d;
    friend ostream& operator<<(ostream& out, const Number& obj);
public:
    Number() : d(0.0) {}
    explicit Number(double ddd) : d(ddd) 
    {
        cout << "Number(" << ddd << ") called." << endl; 
    }
    const Number operator+(const Number& right) const {return Number(d + right.d);}
    const Number operator-(const Number& right) const {return Number(d - right.d);}
    const Number operator*(const Number& right) const {return Number(d * right.d);}
    const Number operator/(const Number& right) const 
    {
        if(right.d != 0)
            return Number(d / right.d);
        else
            return Number(0);
    }
    Number& operator=(const Number& right)
    {
        if(this == &right)
            return *this;
        d = right.d;
        return *this;
    }
    Number& operator=(const double& right)
    {
        if(this->d == right)
            return *this;
        d = right;
        return *this;
    }

    operator double()
    {
        cout << "operator double() called." << endl;
        return double(d);
    }
};

void someFunc(double d) {cout << "someFunc() called." << endl;}

ostream& operator<<(ostream& out, const Number& obj)
{
    out << obj.d;
    return out;
}

int main()
{
    Number a, b, c, d(4.5);
    a = 1.2;
    b = 3.4;
    c = 7.8;
    someFunc(a);

    cout << "\na = " << a
         << "\nb = " << b
         << "\nc = " << c
         << "\nd = " << d
         << "\na + b = " << a + b
         << "\nd - c = " << d - c
         << "\na * d = " << a * d
         << "\nd / b = " << d / b
         << "\n(a + b * c) - d / a = " << (a + b * c) - d / a
         << endl;
}