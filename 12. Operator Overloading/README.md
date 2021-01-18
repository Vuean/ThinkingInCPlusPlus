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

运算符重载的使用是相当受限制的：不能使用C中当前没有意义的运算符（例如用**代表求幕）；不能改变运算符的优先级；不能改变运算符的参数个数。

### 12.3.1 一元运算符

下面的例子显示了重载所有一元运算符的语法，有全局函数形式（非成员的友元函数）也有成员函数形式。它们将扩充前面给出的类`Integer`并且增加一个新类`byte`。

> 代码示例：
[C12_02_OverloadingUnaryOperators.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/12.%20Operator%20Overloading/C12_02_OverloadingUnaryOperators.cpp)

```C++
    // C12_02_OverloadingUnaryOperators.cpp
    #include <iostream>
    using namespace std;

    class Integer
    {
        long i;
        Integer* This() {return this;}
    public:
        Integer(long ll = 0) : i(ll) {}
        // No side effects takes const& argument:
        friend const Integer& operator+(const Integer& a);
        friend const Integer operator-(const Integer& a);
        friend const Integer operator~(const Integer& a);
        friend Integer* operator&(Integer& a);
        friend int operator!(const Integer& a);

        // side effects have non-const& argument:
        // Prefix:
        friend const Integer& operator++(Integer& a);
        // Prefix:
        friend const Integer operator++(Integer& a, int);
        // Prefix:
        friend const Integer& operator--(Integer& a);
        // Prefix:
        friend const Integer operator--(Integer& a, int);
    };

    // Global operators:
    const Integer& operator+(const Integer& a)
    {
        cout << "+Integer\n";
        return a;   // Unary(一元的) + has n o effect
    }

    const Integer operator-(const Integer& a)
    {
        cout << "+Integer\n";
        return Integer(-a.i);
    }

    const Integer operator~(const Integer& a) 
    {
        cout << "~Integer\n" ;
        return Integer(~a.i);
    }

    Integer* operator&(Integer& a) 
    {
        cout << "&Integer\n" ;
        return a.This();    // &a is recursive(递归的).
    }

    int operator!(const Integer& a)
    {
        cout << "!Integer\n";
        return !a.i;
    }

    // Prefix; return incremented value
    const Integer& operator++(Integer& a)
    {
        cout << "++Integer\n";
        a.i++;
        return a;
    }

    // Postfix; return the value before increment:
    const Integer operator++(Integer& a, int)
    {
        cout << "++Integer\n";
        Integer before(a.i);
        a.i++;
        return before;
    }

    // Prefix; return decremented value
    const Integer& operator--(Integer& a)
    {
        cout << "--Integer\n";
        a.i--;
        return a;
    }

    // Postfix; return the value be fore decrement:
    const Integer operator--(Integer& a, int)
    {
        cout << "--Integer\n";
        Integer before(a.i);
        a.i--;
        return before;
    }

    // Show that the overloaded operators work:
    void f(Integer a)
    {
        +a;
        -a;
        ~a;
        Integer* ip = &a;
        !a;
        ++a;
        a++;
        --a;
        a--;
    }

    // Member functions (implicit "this") :
    class Byte
    {
        unsigned char b;
    public:
        Byte(unsigned char bb = 0) : b(bb) {}
        // No side effects : const member function:
        const Byte& operator+() const
        {
            cout << "+Byte\n";
            return *this;
        }
        const Byte operator-() const
        {
            cout << "-Byte\n";
            return Byte(-b);
        }
        const Byte operator~() const
        {
            cout << "~Byte\n";
            return Byte(~b);
        }
        Byte operator!() const
        {
            cout << "!Byte\n";
            return Byte(!b);
        }
        Byte* operator&()
        {
            cout << "&Byte\n";
            return this;
        }
        // Side effects: non-const member function:
        const Byte& operator++() 
        { // Prefix
            cout << "++Byte\n";
            b++;
            return *this;
        }
        const Byte operator++(int) 
        { // Prefix
            cout << "Byte++\n";
            Byte before(b);
            b++;
            return before;
        }
        const Byte& operator--() 
        { // Prefix
            cout << "--Byte\n";
            --b;
            return *this;
        }
        const Byte operator--(int) 
        { // Prefix
            cout << "Byte--\n";
            Byte before(b);
            --b;
            return before;
        }
    };

    void g(Byte b)
    {
        +b;
        -b;
        ~b;
        Byte* bp = &b;
        !b;
        ++b;
        b++;
        --b;
        b--;
    }

    int main()
    {
        Integer a;
        f(a);
        Byte b;
        g(b);
    }
```

#### 12.3.1.1 自增和自减

