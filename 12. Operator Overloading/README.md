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

用户所见到的是对前缀和后缀版本调用不同的函数。然而，实质上这两个函数调用有着不同的标记，所以它们指向两个不同的函数体。编译器为int参数传递一个哑元常量值（因为这个值永远不被使用，所以它永远不会给出一个标识符）用来为后缀版产生不同的标记。

### 12.3.2 二元运算符

下面的清单为二元运算符重复了OverloadingUnaryOperators.cpp，于是就有了所有可重载运算符的例子。全局版本和成员函数版本都在里面。

> 代码示例：
[C12_03_Integer.h](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/12.%20Operator%20Overloading/C12_03_Integer.h)

```C++
    // C12_03_Integer.h
    // Non-member overloaded operators
    #ifndef INTEGER_H
    #define INTEGER_H
    #include <iostream>
    // Non-member functions:
    class Integer
    {
        long i;
    public:
        Integer(long ll = 0) : i(ll) {}
        // Operators that create new, modified value:
        friend const Integer operator+(const Integer& left, const Integer& right);
        friend const Integer operator-(const Integer& left, const Integer& right);    
        friend const Integer operator*(const Integer& left, const Integer& right);
        friend const Integer operator/(const Integer& left, const Integer& right);
        friend const Integer operator%(const Integer& left, const Integer& right);
        friend const Integer operator^(const Integer& left, const Integer& right);
        friend const Integer operator&(const Integer& left, const Integer& right);
        friend const Integer operator|(const Integer& left, const Integer& right);
        friend const Integer operator<<(const Integer& left, const Integer& right);
        friend const Integer operator>>(const Integer& left, const Integer& right);
        // Assignments modify & return lvalue:
        friend Integer& operator+=(Integer& left, const Integer& right);
        friend Integer& operator-=(Integer& left, const Integer& right);
        friend Integer& operator*=(Integer& left, const Integer& right);
        friend Integer& operator/=(Integer& left, const Integer& right);
        friend Integer& operator%=(Integer& left, const Integer& right);
        friend Integer& operator^=(Integer& left, const Integer& right);
        friend Integer& operator&=(Integer& left, const Integer& right);
        friend Integer& operator|=(Integer& left, const Integer& right);
        friend Integer& operator>>=(Integer& left, const Integer& right);
        friend Integer& operator<<=(Integer& left, const Integer& right);
        // Conditional operators return true/false:
        friend int operator==(const Integer& left, const Integer& right);
        friend int operator!=(const Integer& left, const Integer& right);
        friend int operator<(const Integer& left, const Integer& right);
        friend int operator>(const Integer& left, const Integer& right);
        friend int operator<=(const Integer& left, const Integer& right);
        friend int operator>=(const Integer& left, const Integer& right);
        friend int operator&&(const Integer& left, const Integer& right);
        friend int operator||(const Integer& left, const Integer& right);
        // Write the contents to an ostream:
        void print(std::ostream& os) const {os << i;}
    };

    #endif // INTEGER_H
```

> 代码示例：
[C12_03_Integer.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/12.%20Operator%20Overloading/C12_03_Integer.cpp)

```C++
    // C12_03_Integer.cpp
    // Implementation of overloaded operators
    #include "C12_03_Integer.h"
    #include "..\require.h"

    const Integer operator+(const Integer& left, const Integer& right)
    {
        return Integer(left.i + right.i);
    }

    const Integer operator-(const Integer& left, const Integer& right)
    {
        return Integer(left.i - right.i);
    }

    const Integer operator*(const Integer& left, const Integer& right)
    {
        return Integer(left.i * right.i);
    }

    const Integer operator/(const Integer& left, const Integer& right)
    {
        require(right.i != 0, "divide by zero");
        return Integer(left.i / right.i);
    }

    const Integer operator%(const Integer& left, const Integer& right)
    {
        require(right.i != 0, "dodulo by zero");
        return Integer(left.i % right.i);
    }

    const Integer operator^(const Integer& left, const Integer& right)
    {
        return Integer(left.i ^ right.i);
    }

    const Integer operator&(const Integer& left, const Integer& right)
    {
        return Integer(left.i & right.i);
    }

    const Integer operator|(const Integer& left, const Integer& right)
    {
        return Integer(left.i | right.i);
    }

    const Integer operator<<(const Integer& left, const Integer& right)
    {
        return Integer(left.i << right.i);
    }

    const Integer operator>>(const Integer& left, const Integer& right)
    {
        return Integer(left.i >> right.i);
    }

    // Assignments modify & return lvalue:
    Integer& operator+=(Integer& left, const Integer& right)
    {
        if(&left == &right){/*self-assignment*/}
        left.i += right.i;
        return left;
    }

    Integer& operator-=(Integer& left, const Integer& right)
    {
        if(&left == &right){/*self-assignment*/}
        left.i -= right.i;
        return left;
    }

    Integer& operator*=(Integer& left, const Integer& right)
    {
        if(&left == &right){/*self-assignment*/}
        left.i *= right.i;
        return left;
    }

    Integer& operator/=(Integer& left, const Integer& right)
    {
        require(right.i != 0, "divide by zero");
        if(&left == &right){/*self-assignment*/}
        left.i /= right.i;
        return left;
    }

    Integer& operator%=(Integer& left, const Integer& right)
    {
        require(right.i != 0, "modulo by zero");
        if(&left == &right){/*self-assignment*/}
        left.i %= right.i;
        return left;
    }

    Integer& operator^=(Integer& left, const Integer& right)
    {
        if(&left == &right){/*self-assignment*/}
        left.i ^= right.i;
        return left;
    }

    Integer& operator&=(Integer& left, const Integer& right)
    {
        if(&left == &right){/*self-assignment*/}
        left.i &= right.i;
        return left;
    }

    Integer& operator|=(Integer& left, const Integer& right)
    {
        if(&left == &right){/*self-assignment*/}
        left.i |= right.i;
        return left;
    }

    Integer& operator>>=(Integer& left, const Integer& right)
    {
        if(&left == &right){/*self-assignment*/}
        left.i >>= right.i;
        return left;
    }

    Integer& operator<<=(Integer& left, const Integer& right)
    {
        if(&left == &right){/*self-assignment*/}
        left.i <<= right.i;
        return left;
    }

    // Conditional operators return true/false:
    int operator==(const Integer& left, const Integer& right)
    {
        return left.i == right.i;
    }

    int operator!=(const Integer& left, const Integer& right)
    {
        return left.i != right.i;
    }

    int operator>(const Integer& left, const Integer& right)
    {
        return left.i > right.i;
    }

    int operator<(const Integer& left, const Integer& right)
    {
        return left.i < right.i;
    }

    int operator>=(const Integer& left, const Integer& right)
    {
        return left.i >= right.i;
    }

    int operator<=(const Integer& left, const Integer& right)
    {
        return left.i <= right.i;
    }

    int operator&&(const Integer& left, const Integer& right)
    {
        return left.i && right.i;
    }

    int operator||(const Integer& left, const Integer& right)
    {
        return left.i || right.i;
    }
```

> 代码示例：
[C12_04_IntegerTest.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/12.%20Operator%20Overloading/C12_04_IntegerTest.cpp)

```C++
    // C12_04_IntegerTest.cpp
    #include"C12_03_Integer.h"
    #include<fstream>
    using namespace std;
    ofstream out("IntegerTest.out");
    void h(Integer& c1, Integer& c2)
    {
        // A complex expression:
        c1 += c1 * c2 + c2 % c1;
        #define TRY(OP) \
            out << "c1 = "; c1.print(out); \
            out << "c2 = "; c2.print(out); \
            out << "; c1 " #OP " c2 produces "; \
            (c1 OP c1).print(out); \
            out << endl;
        TRY(+) TRY(-) TRY(*) TRY(/)
        TRY(%) TRY(^) TRY(&) TRY(|)
        TRY(<<) TRY(>>) TRY(+=) TRY(-=)
        TRY(*=) TRY(/=) TRY(%=) TRY(^=)
        TRY(&=) TRY(|=) TRY(>>=) TRY(<<=)
        // Conditionals:
        #define TRYC(OP) \
            out << "c1 = "; c1.print(out); \
            out << ", c2 = "; c2.print(out); \
            out << "; c1 " #OP " c2 produces "; \
            out << (c1 OP c2); \
            out << endl;
        TRYC(<) TRYC(>) TRYC(==) TRYC( !=) TRYC(<=)
        TRYC(>=) TRYC(&&) TRYC(||)
    }

    int main()
    {
        cout << "friend functions" << endl;
        Integer c1(47), c2(9);
        h(c1, c2);
    }
```

> 代码示例：
[C12_05_Byte.h](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/12.%20Operator%20Overloading/C12_05_Byte.h)

```C++
    // C12_05_Byte.h
    // Member overloaded operators
    #ifndef BYTE_H
    #define BYTE_H
    #include "../require.h"
    #include <iostream>
    // Member functions (implicit "this"):
    class Byte
    {
        unsigned char b;
    public:
        Byte(unsigned char bb = 0) : b(bb) {}
        // No side effects: const member functions
        const Byte operator+(const Byte& right) const
        {
            return Byte(b + right.b);
        }
        const Byte operator-(const Byte& right) const
        {
            return Byte(b - right.b);
        }
        const Byte operator*(const Byte& right) const
        {
            return Byte(b * right.b);
        }
        const Byte operator/(const Byte& right) const
        {
            require(right.b != 0), "diveded by zero";
            return Byte(b / right.b);
        }
        const Byte operator%(const Byte& right) const
        {
            require(right.b != 0), "modulo by zero";
            return Byte(b % right.b);
        }
        const Byte operator^(const Byte& right) const
        {
            return Byte(b ^ right.b);
        }
        const Byte operator&(const Byte& right) const
        {
            return Byte(b & right.b);
        }
        const Byte operator|(const Byte& right) const
        {
            return Byte(b | right.b);
        }
        const Byte operator<<(const Byte& right) const
        {
            return Byte(b << right.b);
        }
        const Byte operator>>(const Byte& right) const
        {
            return Byte(b >> right.b);
        }

        // Assignments modify & return lvalue:
        // operator= can only be a member function:
        Byte& operator=(const Byte& right)
        {
            // Handle self-assignment"
            if(this == & right) return *this;
            b = right.b;
            return *this;
        }
        Byte& operator+=(const Byte& right)
        {
            if(this == & right) /*self-assignment*/;
            b += right.b;
            return *this;
        }
        Byte& operator-=(const Byte& right)
        {
            if(this == & right) /*self-assignment*/;
            b -= right.b;
            return *this;
        }
        Byte& operator*=(const Byte& right)
        {
            if(this == & right) /*self-assignment*/;
            b *= right.b;
            return *this;
        }
        Byte& operator/=(const Byte& right)
        {
            require(right.b != 0), "diveded by zero";
            if(this == & right) /*self-assignment*/;
            b /= right.b;
            return *this;
        }
        Byte& operator%=(const Byte& right)
        {
            require(right.b != 0), "modulo by zero";
            if(this == & right) /*self-assignment*/;
            b %= right.b;
            return *this;
        }
        Byte& operator^=(const Byte& right)
        {
            if(this == & right) /*self-assignment*/;
            b ^= right.b;
            return *this;
        }
        Byte& operator&=(const Byte& right)
        {
            if(this == & right) /*self-assignment*/;
            b &= right.b;
            return *this;
        }
        Byte& operator|=(const Byte& right)
        {
            if(this == & right) /*self-assignment*/;
            b |= right.b;
            return *this;
        }
        Byte& operator>>=(const Byte& right)
        {
            if(this == & right) /*self-assignment*/;
            b >>= right.b;
            return *this;
        }
        Byte& operator<<=(const Byte& right)
        {
            if(this == & right) /*self-assignment*/;
            b <<= right.b;
            return *this;
        }
        // Conditional operators return true/false:
        int operator==(const Byte& right) const
        {
            return b == right.b;
        }
        int operator!=(const Byte& right) const
        {
            return b != right.b;
        }
        int operator<(const Byte& right) const
        {
            return b < right.b;
        }
        int operator>(const Byte& right) const
        {
            return b > right.b;
        }
        int operator<=(const Byte& right) const
        {
            return b <= right.b;
        }
        int operator>=(const Byte& right) const
        {
            return b >= right.b;
        }
        int operator&&(const Byte& right) const
        {
            return b && right.b;
        }
        int operator||(const Byte& right) const
        {
            return b || right.b;
        }
        // write the contents to an ostream:
        void print(std::ostream& os) const
        {
            os << "0x" << std::hex << int(b) << std::dec;
        }
    };
    #endif // BYTE_H
```

> 代码示例：
[C12_06_ByteTest.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/12.%20Operator%20Overloading/C12_06_ByteTest.cpp)

```C++
    // C12_06_ByteTest.cpp
    #include "C12_05_Byte.h"
    #include <fstream>
    using namespace std;
    ofstream out("ByteTest.out");
    void k(Byte& b1, Byte& b2)
    {
        b1 = b1 * b2 + b2 % b1;
    }

    #define TRY2(OP) \
        out << "b1 = "; b1.print(out); \
        out << ", b2 = "; b2.print(out); \
        out << "; b1 " #OP " b2 produces "; \
        (b1 OP b2).print(out); \
        out << endl;

    b1 = 9; b2 = 47;

    TRY2(+) TRY2(-) TRY2(*) TRY2(/)
    TRY2(%) TRY2(^) TRY2(&) TRY2(|)
    TRY2(<<) TRY2(>>) TRY2(+=) TRY2(-=)
    TRY2(*=) TRY2(/=) TRY2(%=) TRY2(^=)
    TRY2(&=) TRY2(!=) TRY2(>>=) TRY2(<<=)
    TRY2(=) // Assignment operator

    // Conditionals:
    #define TRYC2 (OP) \
        out << "b1 ="; b1.ptint(out); \
        out << ", b2 . = ."; b2.print (out) ; \
        out << "; b1 " #OP " b2 produces "; \
        out « (b1 OP b2 ); \
        out << endl;
    b1 = 9; b2 = 47;
    TRYC2(<) TRYC2(>) TRYC2(==) TRYC2(!=) 
    TRYC2(<=) TRYC2(>=) TRYC2(&&) TRYC2(||)

    // Chained assignment
    Byte b3 = 92;
    b1 = b2 = b3;

    int main()
    {
        out << "member functions: " << endl;
        Byte b1(47), b2(9);
        k(b1, b2);
    }
```

可以看到`operator=`只允许作为成员函数。

### 12.3.3 参数和返回值

虽然可以用任何需要的方式传递和返回参数，但在这些例子中所用的方式却不是随便选的，其遵循一定的模式：

1. 对于任何函数参数，如果仅需要从参数中读而不改变它，默认地应当作为`const`引用来传递它；
2. 返回值的类型取决千运算符的具体含义；
3. 所有赋值运算符均改变左值；
4. 对于逻辑运算符，人们希望至少得到一个int返回值，最好是bool返回值。

对于有前缀和后缀版本的运算符，如自增或自减，两者均改变了对象。但前缀版本返回原对象：所以只需作为一个引用返回`*this`。因为后缀版本返回改变之前的值，所以必须创建一个代表这个值的独立对象并返回。因此，如果想保持本意，对于后缀必须通过传值方式返回。

但还存在一个问题：**它们应该按常最还是按非常量返回？**如果允许对象被改变，而有的人写了表达式`(++a).func()`，那么`func()`作用在`a`上。但对于表达式`(a++).func()`，`func()`作用在通过后缀`operator++`返回的临时对象上。临时对象自动定为常量，所以这一操作会被编译器阻止。但为了一致性，两者都是常量更有意义，这里就是如此。我们可以选择让前缀版本是非常量的，而后缀版本是常量的。

#### 12.3.3.1 作为常量通过传值方式返回

作为常量通过传值方式返回，开始看起来有些微妙，所以值得多加解释。现在考虑二元运算符`+`。假设在表达式`f(a+b)`中使用它，`a+b`的结果变为一个临时对象，这个对象用于对`f()`的调用中。因为它是临时的，自动被定为常量，所以无论是否使返回值为常量都没有影响。

然而，也可能发送一个消息给`a+b`的返回值而不是仅传递给一个函数。例如，可以写表达式`(a+b).g()`，其中`g()`是`Integer`的成员函数。这里，通过设返回值为常量，规定了对于返回值只有常量成员函数才可以被调用。用常量是恰当的，这是因为这样可以使我们不用在对象中存储可能有价值的信息，而该信息很可能是会被丢失的。

#### 12.3.3.2 返回值优化

通过传值方式返回要创建新对象时，应注意使用的形式。例如在`operator+`：`return Integer(left.i + right.i);`。

乍看起来这像是一个“对一个构造函数的调用”，其实并非如此。这是临时对象语法，它是在说：“创建一个临时`Integer`对象并返回它”。据此我们可能认为如果创建一个有名字的局部对象并返回它结果将会是一样的。其实不然，如：

```C++
    Integer tmp(left.i + right.i);
    return tmp;
```

将发生三件事。首先，创建`tmp`对象，其中包括构造函数的调用。然后，拷贝构造函数把`tmp`拷贝到外部返回值的存储单元里。最后，当`tmp`在作用域的结尾时调用析构函数。

相反，“返回临时对象”的方式是完全不同的。当编译器看到我们这样做时，它明白对创建的对象没有其他需求，只是返回它，所以编译器直接地把这个对象创建在外部返回值的内存单元。因为不是真正创建一个局部对象，所以仅需要一个普通构造函数调用（不需要拷贝构造函数），且不会调用析构函数。这种方法不需要什么花费，因此效率是非常高的，但程序员要理解这些。这种方式常被称作**返回值优化**(**return value optimization**)。

### 12.3.4 不常用的运算符

下标运算符`operator[]`，必须是成员函数井且它只接受一个参数。因为它所作用的对象应该像数组一样操作，可以经常从这个运算符返回一个引用，所以它可以被很方便地用于等号左侧。这个运算符经常被重载，可以在本书其他部分看到相关的例子。

#### 12.3.4.1 operator,

当逗号出现在一个对象左右，而该对象的类型是逗号定义所支持的类型时，将调用逗号运算符。然而，`operator,`调用的目标不是函数参数表，而是被逗号分隔开的、没有被括号括起来的对象。除了使语言保持一致性外，这个运算符似乎没有许多实际用途。下面的例子说明了当逗号出现在对象前面以及后面时，逗号函数调用的方式：

> 代码示例：
[C12_07_OverloadingOperatorComma.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/12.%20Operator%20Overloading/C12_07_OverloadingOperatorComma.cpp)

```C++
    // C12_07_OverloadingOperatorComma.cpp
    #include <iostream>
    using namespace std;

    class After
    {
    public:
        const After& operator,(const After&) const
        {
            cout << "After::operator,()" << endl;
            return *this;
        }
    };

    class Before {};

    Before& operator,(int, Before& b)
    {
        cout << "Before::operator,()" << endl;
        return b;
    }

    int main()
    {
        After a, b;
        a, b;   // Operator comma, called

        Before c;
        1, c;
    }
```

全局函数允许逗号放在被讨论的对象的前面。这里的用法既晦涩又可疑。虽然还可以再把一个逗号分隔的参数表当做更加复杂的表达式的一部分，但这太灵活了，大多数情况下不能使用。

#### 12.3.4.2 operator->

当希望一个对象表现得像一个指针时，通常就要用到`operator->`。由于这样一个对象比一般的指针有着更多与生俱来的灵巧性，于是常被称作**灵巧指针**(**smart pointer**)。如果想用类包装一个指针以使指针安全，或是在**迭代器**(**iterator**)普通的用法中，这样做会特别有用。

**迭代器**是一个对象，这个对象可以作用于其他对象的容器或集合上，每次选择它们中的一个而不用提供对容器的直接访问。

指针间接引用运算符一定是一个成员函数。它有着额外的、非典型的限制：它**必须返回一个对象**（或对象的引用），该对象也有一个指针间接引用运算符；或者**必须返回一个指针**，被用于选择指针间接引用运算符箭头所指向的内容。下面是一个简单的例子：

> 代码示例：
[C12_08_SmartPointer.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/12.%20Operator%20Overloading/C12_08_SmartPointer.cpp)

```C++
    // C12_08_SmartPointer.cpp
    #include <iostream>
    #include <vector>
    #include "../require.h"
    using namespace std;

    class Obj
    {
        static int i, j;
    public:
        void f() const {cout << i++ << endl;}
        void g() const {cout << j++ << endl;}
    };

    // Static member definitions:
    int Obj::i = 47;
    int Obj::j = 11;

    // Container:
    class ObjContainer
    {
        vector<Obj*> a;
    public:
        void add(Obj* obj) {a.push_back(obj);}
        friend class SmartPointer;
    };

    class SmartPointer
    {
        ObjContainer& oc;
        int index;
    public:
        SmartPointer(ObjContainer& objc) : oc(objc)
        {
            index = 0;
        }
        // Return value indicates end of list:
        bool operator++()
        {
            if(index >= oc.a.size()) return false;
            if(oc.a[++index] == 0) return false;
            return true;
        }
        bool operator++(int)
        {
            return operator++();
        }
        Obj* operator->() const
        {
            require(oc.a[index] != 0, "Zero value "
                "returned by SmartPointer::operator->()");
            return oc.a[index];
        }
    };

    int main()
    {
        const int sz = 10;
        Obj o[sz];
        ObjContainer oc;
        for(int i = 0; i < sz; i++)
            oc.add(&o[i]);
        SmartPointer sp(oc);    // Create an iterator
        do{
            sp->f();    // Pointer dereference operator call
            sp->g();
        }while(sp++);
    }
```

类`SmartPointer`被声明为友元类，所以它允许进入这个容器内。

在`main()`中，一旦`Obj`对象装入容器`oc`，一个`SmartPointer`类的SP就创建了，并可进行调用：`sp->f();`

尽管`sp`实际上并没有成员函数`f()`和`g()`，但指针间接引用运算符自动地为用`SmartPointer::operator->`返回的`Obj*`调用那些函数。编译器进行所有检查以保证函数调用正确。

#### 12.3.4.3 嵌入的迭代器

更常见的是，“灵巧指针”和“迭代器”类嵌入它所服务的类中。前面的例子可按如下重写，以在`ObjContainer`中嵌入`SmartPointer`。

> 代码示例：
[C12_09_NestedSmartPointer.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/12.%20Operator%20Overloading/C12_09_NestedSmartPointer.cpp)

```C++
    // C12_09_NestedSmartPointer.cpp
    #include <iostream>
    #include <vector>
    #include "../require.h"
    using namespace std;

    class Obj
    {
        static int i, j;
    public:
        void f() const {cout << i++ << endl;}
        void g() const {cout << j++ << endl;}
    };

    // Static member definitions:
    int Obj::i = 47;
    int Obj::j = 11;

    // Container:
    class ObjContainer
    {
        vector<Obj*> a;
    public:
        void add(Obj* obj) {a.push_back(obj);}
        class SmartPointer;
        friend SmartPointer;
        class SmartPointer
        {
            ObjContainer& oc;
            unsigned int index;
        public:
            SmartPointer(ObjContainer& objc) : oc(objc)
            {
                index = 0;
            }
            // Return value indicates end of list:
            bool operator++()
            {
                if(index >= oc.a.size()) return false;
                if(oc.a[++index] == 0) return false;
                return true;
            }
            bool operator++(int)
            {
                return operator++();
            }
            Obj* operator->() const
            {
                require(oc.a[index] != 0, "Zero value "
                    "returned by SmartPointer::operator->()");
                return oc.a[index];
            }
        };
        // Function to produce a smart pointer that points to
        // the beginning og the ObjContainer:
        SmartPointer begin()
        {
            return SmartPointer(*this);
        }
    };

    int main()
    {
        const int sz = 10;
        Obj o[sz];
        ObjContainer oc;
        for(int i = 0; i < sz; i++)
            oc.add(&o[i]);
        ObjContainer::SmartPointer sp = oc.begin();    // Create an iterator
        do{
            sp->f();    // Pointer dereference operator call
            sp->g();
        }while(++sp);
    }
```

嵌入类中后，有两点不同：首先是在类的声明中说明它是一个友元类。

```C++
    class SmartPointer;
    friend SmartPointer;
```

编译器首先在被告知类是友元的之前，必须知道该类是存在的。

第二个不同之处是在`ObjContainer`的成员函数`begin()`中，`begin()`产生一个指向`ObjContainer`序列开头的`SmartPointer`。

#### 12.3.4.4 operator->*

`operator->*`是一个二元运算符，其行为与所有其他二元运算符类似。它是专为模仿前一章介绍的内部数据类型的成员指针行为而提供的。

