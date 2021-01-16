#include <iostream>
using namespace std;

class Ex5
{
    int x;
public:
    Ex5() : x(0) {}
    Ex5(Ex5& tmp) : x(tmp.x) {}
    void change() {x += 10;}
    void print() {cout << "x = " << x << endl;}
    void constFunc() const {cout << "Ex5::constFunc()" << endl;} 
};

Ex5& f(Ex5* ex)
{
    cout << "f() begin:" << endl;
    cout << "ex->x: " << endl;
    ex->print();
    ex->change();
    Ex5& exptr = *ex;
    cout << "exptr->x: " << endl;
    exptr.print();
    exptr.constFunc();
    cout << "f() end:" << endl;
    return exptr;
}

const Ex5& f2(const Ex5& ex)
{
    const Ex5& exptr = ex;
    // 对象含有于成员函数“Ex5::print”不兼容的类型限定符
    // 对象类型是：const Ex5
    // exptr.print();
    // exptr.change();
    exptr.constFunc();
    return exptr;
}

int main()
{
    Ex5 tmp;
    f(&tmp);
    f2(tmp);
}