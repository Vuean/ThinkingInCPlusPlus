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
    
    // 前缀
    IntClass& operator++()
    {
        i++;
        return *this;
    }
    IntClass& operator--()
    {
        i--;
        return *this;
    }

    // 后缀
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

    IntClass e(10);
    (++e).print(cout);
    // 对象含有与成员 函数 "IntClass::print" 不兼容的类型限定符 
    // -- 对象类型是:  const IntClass
    (e++).print(cout);
}