// C8_06_ConstReturnValues.cpp
// Constant return by value
// Result cannot be used as a lvalue

class X
{
    int i;
public:
    X(int ii = 0);
    void modify();
};

X::X(int ii) { i = ii; }

void X::modify() {i++;}

X f5()
{
    return X();
}

const X f6()
{
    return X();
}

void f7(X& x)
{
    // pass by non-const reference
    x.modify();
}

int main()
{
    f5() = X(1);    // OK -- non-const return value
    f5().modify(); // OK

    // cannot bind non-const lvalue reference of type 'X&' to an rvalue of type 'X'
    // f7(f5());       // Causes warning
    // Causes compile-time errors:
    
    // 报错：没有与这些操作匹配的“=”运算符
    // 操作数类型为：const X = X;
    // f6() = X(1);

    // 报错：对象含有与成员函数"X::modify"不兼容的类型限定符
    // 对象类型是：const X
    // f6().modify();
    
     // 报错：将"X&"类型的引用绑定到"const X"类型的初始值设定项时，
     // 限定符被丢弃
    // f7(f6());
}