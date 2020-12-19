#include <iostream>
using namespace std;

class X
{
    int i;
public:
    X(int ii = 0);
    void modify();
};

X::X(int ii) 
{
    i = ii;
    cout << "X(): " << i << endl;
}

void X::modify()
{
    i++;
    cout << "modify() i = " << i << endl;
}

X f5()
{
    return X();
}

const X f6()
{
    return X();
}

void f7(X& _x)
{
    _x.modify();
}

int main()
{
    f5() = X(1);
    f5().modify();
    // cannot bind non-const lvalue reference of type 'X&' to an rvalue of type 'X'
    // f7(f5());

    // 没有与这些操作数匹配的 "=" 运算符 -- 操作数类型为:  const X = X
    // f6() = X(1);

    //对象含有与成员 函数 "X::modify" 不兼容的类型限定符 -- 对象类型是:  const X
    // f6().modify();

    // 将 "X &" 类型的引用绑定到 "const X" 类型的初始值设定项时，限定符被丢弃
    // f7(f6());
}