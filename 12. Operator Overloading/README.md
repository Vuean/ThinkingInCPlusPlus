# 第十二章 运算符重载

**运算符重载**(**operator overloading**)只是一种“语法上的方便”(syntactic sugar)，也就是说它只是另一种函数调用的方式。

运算符的使用和普通的函数调用有两点不同。首先语法上是不同的，“调用”运算符时要把运算符放置在参数之间，有时在参数之后。第二个不同是由编译器决定调用哪一个“函数”。

## 12.1 两个极端

## 12.2 语法

定义重载的运算符就像定义函数，只是该函数的名字是`operator@`，这里`@`代表了被重载的运算符。函数参数表中参数的个数取决于两个因素：

1) 运算符是一元的（一个参数）还是二元的（两个参数）；
2) 运算符被定义为全局函数（对于一元是一个参数，对于二元是两个参数）还是成员函数。

> 代码示例：
[C12_01_OperatorOverloadingSyntax.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/12.%20Operator%20Overloading/C12_01_OperatorOverloadingSyntax.cpp)

```C++
    // C12_01_OperatorOverloadingSyntax.cpp
    #include <iostream>
    using namespace std;

    class Integer
    {
        int i;
    public:
        Integer(int ii) : i(ii) {}
        const Integer operator+(const Integer& rv) const 
        {
            cout << "operator+" << endl;
            return Integer(i + rv.i);
        }
        Integer& operator+=(const Integer& rv)
        {
            cout << "operator+=" << endl;
            i += rv.i;
            return *this;
        }
        void print() {cout << i << endl;}
    };

    int main()
    {
        cout << "built-in types:" << endl;
        int i= 1, j = 2, k = 3;
        k += i + j;
        cout << "user-defined types:" << endl;
        Integer ii(1), jj(2), kk(3);
        kk += ii + jj;
        kk.print();
    }
```

这两个重载的运算符被定义为内联成员函数，在它们被调用时会显示信息。对于二元运算符，惟一的参数是出现在运算符右侧的那个操作数。当一元运算符被定义为成员函数时，是没有参数的。所调用的成员函数属于运算符左侧的那个对象。

## 12.3 可重载的运算符

