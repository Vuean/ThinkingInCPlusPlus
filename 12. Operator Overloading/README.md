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

与`operator->*`一样，指向成员的指针间接引用运算符通常同某种代表“灵巧指针”的对象一起使用。在定义`operator->*`时要注意它**必须返回一个对象**，对于这个对象，可以用正在调用的成员函数为参数调用`operator()`。

`operator()`的函数调用必须是成员函数，它是惟一的允许在它里面有任意个参数的函数。

要想创建一个`operator->*`，必须首先创建带有`operator()`类，这是`operator->*`将返回对象的类。该类必须获取一些必要的信息，以使当`operator()`被调用时，指向成员的指针可以对对象进行间接引用。在下面的例子中，`FunctionObject`的构造函数得到并储存指向对象的指针和指向成员函数的指针，然后`operator()`使用这些指针进行实际指向成员的指针的调用。

> 代码示例：
[C12_10_PointerToMemberOperator.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/12.%20Operator%20Overloading/C12_10_PointerToMemberOperator.cpp)

```C++
    // C12_10_PointerToMemberOperator.cpp
    #include <iostream>
    using namespace std;
    class Dog
    {
    public:
        int run(int i) const
        {
            cout << "run\n";
            return i;
        }
        int eat(int i) const
        {
            cout << "eat\n";
            return i;
        }
        int sleep(int i) const
        {
            cout << "ZZZ\n";
            return i;
        }
        typedef int (Dog::*PMF)(int) const;
        // operator->* must return an object that has an operator()
        class FunctionObject
        {
            Dog* ptr;
            PMF pmem;
        public:
            // save the object pointer and member pointer
            FunctionObject(Dog* wp, PMF pmf)
                : ptr(wp), pmem(pmf)
            {
                cout << "FunctionObject constructor\n";
            }
            // Make the call using the object pointer and member pointer
            int operator()(int i) const
            {
                cout << "FunctionObject::operator()\n";
                return (ptr->*pmem)(i);
            }
        };
        FunctionObject operator->*(PMF pmf)
        {
            cout << "operator->*" << endl;
            return FunctionObject(this, pmf);
        }
    };

    int main()
    {
        Dog m;
        Dog::PMF pmf = &Dog::run;
        cout << (m->*pmf)(1) << endl;
        pmf = &Dog::sleep;
        cout << (m->*pmf)(2) << endl;
        pmf = &Dog::eat;
        cout << (m->*pmf)(3) << endl;
    }
```

`Dog`有三个成员函数，它们的参数和返回类型都是`int`。`PMF`是一个`typedef`，用于简化定义一个指向`Dog`成员函数的指向成员的指针。

`operator->*`创建并返回一个`FunctionObject`对象。注意`operator->*`既知道指向成员的指针所调用的对象(`this`)，又知道这个指向成员的指针，并把它们传递给存储这些值的`FunctionObject`构造函数。当`operator->*`被调用时，编译器立刻转而对`operator->*`返回的值调用`operator()`，把已经给`operator->*`的参数传递进去。`FtinctionObject::operator()`得到参数，然后使用存储的对象指针和指向成员的指针间接引用“真实的”指向成员的指针。

### 12.3.5 不能重载的运算符

在可用的运算符集合里存在一些不能重载的运算符。这样限制的通常原因是出于对安全的考虑：如果这些运算符也可以被重载，将会造成危害或破坏安全机制，使得事情变得困难或混淆现有的习惯。

1. 成员选择`operator.`。点在类中对任何成员都有一定的意义。但如果允许它重载，就不能用普通的方法访问成员，只能用指针和指针`operator->`访问。
2. 成员指针间接引用`operator.*`，因为与`operator.`同样的原因而不能重载。
3. 没有求幕运算符。
4. 不存在用户定义的运算符，即不能编写目前运算符集合中没有的运算符。
5. 不能改变优先级规则。

## 12.4 非成员运算符

运算符可能是成员运算符或非成员运算符，但怎么选择呢？总体来说没有差异，它们应该是成员运算符。这样做强调了运算符和类的联合。当左侧操作数是当前类的对象时，运算符会工作得很好。

但有时左侧运贷符是别的类的对象。这种情况通常出现在为输入输出流重载`operator<<`和`>>`时。

> 代码示例：
[C12_11_IostreamOperatorOverloading.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/12.%20Operator%20Overloading/C12_11_IostreamOperatorOverloading.cpp)

```C++
    // C12_11_IostreamOperatorOverloading.cpp
    // Example of non-member overloaded operators
    #include "../require.h"
    #include <iostream>
    #include <sstream>
    #include <cstring>
    using namespace std;

    class IntArray
    {
        enum {sz = 5};
        int i[sz];
    public:
        IntArray() {memset(i, 0, sz * sizeof(*i));}
        int& operator[] (int x)
        {
            require(x >= 0 && x < sz, "IntArray::operator[] out of range");
            return i[x];
        }
        friend ostream& operator<<(ostream& os, const IntArray& ia);
        friend istream& operator>>(istream& is, IntArray& ia);
    };

    ostream& operator<<(ostream& os, const IntArray& ia)
    {
        for(int j = 0; j < ia.sz; j++)
        {
            os << ia.i[j];
            if(j != ia.sz - 1)
                os << ", ";
        }
        os << endl;
        return os;
    }

    istream& operator>>(istream& is, IntArray& ia)
    {
        for(int j = 0; j < ia.sz; j++)
        {
            is >> ia.i[j];
        }
        return is;
    }

    int main()
    {
        stringstream input("47 34 56 72 103");
        IntArray I;
        input >> I;
        I[4] = -1;
        cout << I;
    }
```

被重载的移位运算符通过引用方式传递和返回，所以运算将影响外部对象。如`os << ia.i[j];`会使现有的重载运算函数被调用。

在`main()`中，`iostream`的一种新类型被使用：`stringstream`。该类包含一个`string`（正如此处显示的，它可以由一个char数组创建）并且把它转化为一个`iostream`。这意味着在不打开一个文件或在命令行中键入数据的情况下，移位运算符可以被测试。

### 12.4.1 基本方针

|运算符|建议使用|
 :----: | :-----: |  
|所有一元运算符|成员|
|= () [] -> ->*|必须是成员|
|+= -= /= *= ^= \|= &= %= >>= <<=|成员|
|所有其他二元运算符|非成员|

## 12.5 重载赋值符

在任何时候使用一个“=”代替普通形式的构造函数调用来初始化一个对象时，无论等号右侧是什么，编译器都会寻找一个接受右边类型的构造函数：

> 代码示例：
[C12_12_CopyingVsInitialization.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/12.%20Operator%20Overloading/C12_12_CopyingVsInitialization.cpp)

```C++
    // C12_12_CopyingVsInitialization.cpp
    class Fi
    {
    public:
        Fi() {};
    };

    class Fee
    {
    public:
        Fee(int){}
        Fee(const Fi&) {}
    };

    int main()
    {
        Fee fee = 1;    // Fee(int)
        Fi fi;
        Fee fum = fi;   // Fee(Fi)
    }
```

当处理“=”时，记住这个差别是非常重要的：**如果对象还没有被创建，初始化是需要的，否则使用赋值`operator=`**。

对于初始化，使用“=”可以避免写代码。不用总是用显式的构造函数形式。等号的两种构造形式变为：

```C++
    Fee fee(1);
    Fee fum(fi);
```

### 12.5.1 operator=的行为

在`Integer.h`和`Byte.h`中，可以看到`operator=`仅是成员函数，它密切地与“=”左侧的对象相联系。如果允许定义`operator=`为全局的，那么我们就会试图重新定义内置的"="：

```C++
    int operator=(int, MyType); // Global = not allowed!
```

编译器通过强制`operator=`为成员函数而避开这个问题。

当创建一个`operator=`时，必须从右侧对象中拷贝所有需要的信息到当前的对象以完成为类的“赋值”，对于简单的对象，这是显然的：

> 代码示例：
[C12_13_SimpleAssignment.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/12.%20Operator%20Overloading/C12_13_SimpleAssignment.cpp)

```C++
    // C12_13_SimpleAssignment.cpp
    // Simple operator=()
    #include <iostream>
    using namespace std;

    class Value
    {
        int a, b;
        float c;
    public:
        Value(int aa = 0, int bb = 0, float cc = 0.0)
            : a(aa), b(bb), c(cc) {}
        Value& operator=(const Value& rv)
        {
            a = rv.a;
            b = rv.b;
            c = rv.c;
            return *this;
        }
        friend ostream& operator<<(ostream& os, const Value& rv)
        {
            return os << "a = " << rv.a << ", b = " << rv.b
                << ", c = " << rv.c;
        }
    };

    int main()
    {
        Value a, b(1, 2, 3.3);
        cout << "a: " << a << endl;
        cout << "b: " << b << endl;
        a = b;
        cout << "a after assignment: " << a << endl;
    }
```

这里，“=”左侧的对象拷贝了右侧对象中的所有内容，然后返回它的引用，所以还可以创建更加复杂的表达式。

这个例子犯了一个常见的错误。**当准备给两个相同类型的对象赋值时，应该首先检查一下自赋值(self-assignment)**：这个对象是否对自身赋值了？在一些情况下，例如本例，无论如何执行这些赋值运算都是无害的，但如果对类的实现进行了修改，那么将会出现差异。如果
我们习惯于不做检查，就可能忘记并产生难以发现的错误。

#### 12.5.1.1 类中指针

如果对象里包含指向别的对象的指针将如何？简单地拷贝一个指针意味着以指向相同的存储单元的对象而结束。这里存在两个解决方法，其一是**当做一个赋值运算或一个拷贝构造函数时，最简单的方法是拷贝这个指针所涉及的一切**。

> 代码示例：
[C12_14_CopyingWithPointers.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/12.%20Operator%20Overloading/C12_14_CopyingWithPointers.cpp)

```C++
    // C12_14_CopyingWithPointers.cpp
    // Solving the pointer aliasing problem by
    // duplicating what is pointed to during assignment and copy-construction
    #include "../require.h"
    #include <string>
    #include <iostream>
    using namespace std;
    class Dog
    {
        string nm;
    public:
        Dog(const string& name) : nm(name)
        {
            cout << "Creating Dog: " << *this << endl;
        }
        // Synthesized copy-constructor & operator= are correct
        // Create a Dog from a Dog pointer:
        Dog(const Dog* dp, const string& msg)
            : nm(dp->nm + msg)
        {
            cout << "Copied dog: " << *this << " from " << *dp << endl;
        }
        ~Dog()
        {
            cout << "Deleting Dog: " << *this << endl;
        }
        void rename(const string& newName)
        {
            nm = newName;
            cout << "Dog renamed to: " << *this << endl;
        }
        friend ostream& operator<<(ostream& os, const Dog& d)
        {
            return os << "[" << d.nm << "]";
        }
    };

    class DogHouse
    {
        Dog* p;
        string houseName;
    public:
        DogHouse(Dog* dog, const string& house)
            : p(dog), houseName(house) {}
        DogHouse(const DogHouse& dh)
            : p(new Dog(dh.p, "copy-constructed")), 
            houseName(dh.houseName + "copy-constructed") {}
        DogHouse& operator=(const DogHouse& dh)
        {
            // Check for self-assignment
            if(&dh != this)
            {
                p = new Dog(dh.p, " assigned");
                houseName = dh.houseName + " assigned";
            }
            return *this;
        }
        void renameHouse(const string& newName)
        {
            houseName = newName;
        }
        Dog* getDog() const { return p;}
        ~DogHouse() {delete p;}
        friend ostream& operator<<(ostream& os, const DogHouse& dh)
        {
            return os << "[" << dh.houseName << "] contains" << *dh.p;
        }
    };

    int main()
    {
        DogHouse fidos(new Dog("Fido"), "FidoHouse");
        cout << fidos << endl;
        DogHouse fidos2 = fidos;    // Copy construction
        cout << fidos2 << endl;
        fidos2.getDog()->rename("Spot");
        fidos2.renameHouse("SpotHouse");
        cout << fidos2 << endl;
        fidos = fidos2; // Assignment
        cout << fidos << endl;
        fidos.getDog()->rename("Max");
        fidos.renameHouse("MaxHouse");
    }
```

当类中包含指针时，`DogHouse`含有一个`Dog*`并说明了需要定义的4个函数：所有必需的普通构造函数、拷贝构造函数、`operator=`（无论定义它还是不允许它）和析构函数。

#### 12.5.1.2 引用计数

**引用计数**(**reference counting**)。可以使一块存储单元具有智能，它知道有多少对象指向它。拷贝构造函数或赋值运算意味着把另外的指针指向现在的存储单元并增加引用记数。消除意味着减小引用记数，如果引用记数为0则意味销毁这个对象。

**写拷贝**(**copy-on-write**)：在向这块存储单元写之前，应该确信没有其他人使用它。如果引用记数大于1，在写之前必须拷贝这块存储单元，这样就不会影响他人了。

> 代码示例：
[C12_15_ReferenceCounting.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/12.%20Operator%20Overloading/C12_15_ReferenceCounting.cpp)

```C++
    // C12_15_ReferenceCounting.cpp
    // Reference count, copy-on-write
    #include "../require.h"
    #include <string>
    #include <iostream>
    using namespace std;
    class Dog
    {
        string nm;
        int refcount;
        Dog(const string& name) : nm(name), refcount(1)
        {
            cout << "Creating Dog: " << *this << endl;
        }
        // Prevent assignment
        Dog& operator=(const Dog& rv);
    public:
        // Dog can only be created on the heap:
        static Dog* make(const string& name)
        {
            return new Dog(name);
        }
        Dog(const Dog& d) : nm(d.nm + " copy"), refcount(1)
        {
            cout << "Dog copy-constructor: " << *this << endl;
        }
        ~Dog()
        {
            cout << "Deleting Dog: " << *this << endl;
        }
        void attach()
        {
            ++refcount;
            cout << "Attach Dog: " << *this << endl;
        }
        void detach()
        {
            require(refcount != 0);
            cout << "Detach Dog: " << *this << endl;
            // Destory object if no one is using it:
            if(--refcount == 0) delete this;
        }
        // Conditional copy this Dog.
        // Call before nodifying the Dog, assign resulting pointer to your Dog*.
        Dog* unalias()
        {
            cout << "Unaliasing Dog: " << *this << endl;
            // Don't duplicate if not called:
            if(refcount == 1) return this;
            --refcount;
            // Use copy-constructor to duplicate:
            return new Dog(*this);
        }
        void rename(const string& newName)
        {
            nm = newName;
            cout << "Dog renamed to: " << *this << endl;
        }
        friend ostream& operator<<(ostream& os, const Dog& d)
        {
            return os << "[" << d.nm << "], rc = " << d.refcount;
        }
    };

    class DogHouse
    {
        Dog* p;
        string houseName;
    public:
        DogHouse(Dog* dog, const string& house)
            : p(dog), houseName(house) 
        {
            cout << "Created DogHouse: " << *this << endl;
        }
        DogHouse(const DogHouse& dh)
            : p(dh.p), houseName("copy-constructed" + dh.houseName) 
        {
            p->attach();
            cout << "DogHouse copy-constructor: " << *this << endl;
        }
        DogHouse& operator=(const DogHouse& dh)
        {
            // Check for self-assignment
            if(&dh != this)
            {
                houseName = dh.houseName + " assigned";
                // Clean up what you're using first:
                p->detach();
                p = dh.p;   // like copy-constructor
                p->attach();
            }
            cout << "DogHouse operator= : " << *this << endl;
            return *this;
        }
        // Decrement refcount, conditionally destory
        ~DogHouse()
        {
            cout << "DogHouse Destructors: " << *this << endl;
            p->detach();
        }
        void renameHouse(const string& newName)
        {
            houseName = newName;
        }
        void unalias() {p->unalias();}
        // Copy-on-write. Anytime you modify the contents of the pointer 
        // you must first unalias it:
        void renameDog(const string& newName)
        {
            unalias();
            p->rename(newName);
        }
        // .. or when you allow someone else access:
        Dog* getDog() 
        { 
            unalias();
            return p;
        }
        
        friend ostream& operator<<(ostream& os, const DogHouse& dh)
        {
            return os << "[" << dh.houseName << "] contains" << *dh.p;
        }
    };

    int main()
    {
        DogHouse fidos(Dog::make("Fido"), "FidoHouse"),
                spots(Dog::make("Spot"), "SpotHouse");
        cout << "Entering copy-construction" << endl;
        DogHouse bobs(fidos);
        cout << "After copy-constructing bobs:" << endl;
        cout << "fidos: " << fidos << endl;
        cout << "spots: " << spots << endl;
        cout << "bobs: " << bobs << endl;
        cout << "Entering spots = fidos" << endl;
        spots = fidos;
        cout << "After spots = fidos" << endl;
        cout << "spots: " << spots << endl;
        cout << "Entering self-assignment" << endl;
        bobs = bobs;
        cout << "After self-assignment" << endl;
        cout << "bobs: " << bobs << endl;
        // Comment out the following lines:
        cout << "Entering rename(\"Bob\") " << endl;
        bobs.getDog()->rename("Bob");
        cout << "After rename(\"Bob\") " << endl;
    }
```

类`Dog`是`DogHouse`指向的对象。包含了一个引用记数及控制和读引用记数的函数。同时这里存在一个拷贝构造函数，所以可以从现有的对象创建一个新的`Dog`。

函数`attach()`增加一个`Dog`的引用记数用以指示有另一个对象使用它。函数`detach()`减少引用记数。如果引用记数为0，则说明没有对象使用它，所以通过表达式`delete this`，成员函数销毁它自己的对象。

在进行任何修改（例如为一个`Dog`重命名）之前，必须保证所修改的`Dog`没有被别的对象正在使用。这可以通过调用`DogHouse::unalias()`，它又进而调用`Dog::unalias()`来做到这点。如果引用记数为1（意味着没有别的对象指向这块存储单元），后面这个函数将返回存在的`Dog`指针，但如果引用记数大于1（意味着不只一个对象指向这个`Dog`)就要复制这个`Dog`。

`operator=`处理等号左侧己创建的对象，所以它首先必须通过为`Dog`调用`detach()`来整理这个存储单元。

`operator=`处理等号左侧己创建的对象，所以它首先必须通过为`Dog`调用`detach()`来整理这个存储单元。如果没有其他对象使用它，这个老的`Dog`将被销毁。然后`operator=`重复拷贝构造函数的行为。

#### 12.5.1.3 自动创建operator=

如果没有创建`type::operator=(type)`，编译器将自动创建一个。这个运算符行为模仿自动创建的拷贝构造函数的行为：如果类包含对象（或是从别的类继承的），对于这些对象，`operator=`被递归调用。这被称为**成员赋值**(**memberwise assignment**)。见如下例子：

> 代码示例：
[C12_16_AutomaticOperatorEqual.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/12.%20Operator%20Overloading/C12_16_AutomaticOperatorEqual.cpp)

```C++
    // C12_16_AutomaticOperatorEqual.cpp
    #include <iostream>
    using namespace std;
    class Cargo
    {
    public:
        Cargo& operator=(const Cargo&)
        {
            cout << "inside Cargo::operator=()" << endl;
            return *this;
        }
    };

    class Truck
    {
        Cargo n;
    };

    int main()
    {
        Truck a, b;
        a = b;
    }
```

为`Truck`自动生成的`operator=`调用`Cargo::operator=`。

## 12.6 自动类型转换

在C和C++中，如果编译器看到一个表达式或函数调用使用了一个不合适的类型，它经常会执行一个自动类型转换，从现在的类型到所要求的类型。在C++中，可以通过定义自动类型转换函数来为用户定义类型达到相同效果。这些函数有两种类型：**特殊类型的构造函数**和**重载的运算符**。

### 12.6.1 构造函数转换

如果定义一个构造函数，这个构造函数能把另一类型对象（或引用） 作为它的单个参数，那么这个构造函数允许编译器执行自动类型转换：

> 代码示例：
[C12_17_AutomaticTypeConversion.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/12.%20Operator%20Overloading/C12_17_AutomaticTypeConversion.cpp)

```C++
    // C12_17_AutomaticTypeConversion.cpp
    // Type conversion constructor
    class One
    {
    public:
        One() {}
    };

    class Two
    {
    public:
        Two(const One&) {}
    };

    void f(Two) {}

    int main()
    {
        One one;
        f(one); // Want a Two, has a One
    }
```

当编译器看到`f()`以类One的对象为参数调用时，编译器检查`f()`的声明并注意到它需要一个类Two的对象作为参数。然后，编译器检查是否有从对象One到Two的方法。它发现了构造函数`Two::Two(One)`，`Two::Two(One)`被悄悄地调用，结果对象Two被传递给`f()`。

在这种情况下，自动类型转换避免了定义两个`f()`重载版本的麻烦。然而，代价是调用Two的隐藏构造函数，如果关心`f()`的调用效率的话，那就不要使用这种方法。

#### 12.6.1.1 阻止构造函数转换

有时通过构造函数自动转换类型可能出现问题。为了避开这个麻烦，可以通过在前面加关键字`explicit`（只能用于构造函数）来对上例类Two的构造函数进行修改：

> 代码示例：
[C12_18_ExplicitKeyword.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/12.%20Operator%20Overloading/C12_18_ExplicitKeyword.cpp)

```C++
    // C12_18_ExplicitKeyword.cpp
    // Using the "explicit" keyword
    class One
    {
    public:
        One(){}
    };

    class Two
    {
    public:
        explicit Two(const One&){}
    };

    void f(Two) {}

    int main()
    {
        One one;
        // f(one); // No auto conversion allowed
        f(Two(one));
    }
```

通过使类Two的构造函数显式化，上面代码`f(Two(One))`创建一个从类型One到Two的临时对象。

### 12.6.2 运算符转换

**第二种自动类型转换的方法是通过运算符重载**。可以创建一个成员函数，这个函数通过在关键字`operator`后**跟随想要转换到的类型的方法**，将当前类型转换为希望的类型。这种形式的运算符重载是独特的，因为**没有指定一个返回类型**————**返回类型就是正在重载的运算符的名字**。下面是一个例子：

> 代码示例：
[C12_19_OperatorOverloadingConversion.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/12.%20Operator%20Overloading/C12_19_OperatorOverloadingConversion.cpp)

```C++
    // C12_19_OperatorOverloadingConversion.cpp
    class Three
    {
        int i;
    public:
        Three(int ii = 0, int = 0) : i(ii) {}
    };

    class Four
    {
        int x;
    public:
        Four(int xx) : x(xx) {}
        operator Three() const { return Three(x);}
    };

    void g(Three){}

    int main()
    {
        Four four(1);
        g(four);
        g(1);   // Calls Three(1, 0)
    }
```

用构造函数技术，目的类执行转换。然而使用运算符技术，是源类执行转换。然而，创建一个单一参数的构造函数总是需要定义一个自动类型转换。另外，使用构造函数技术没有办法实现从用户定义类型向内置类型转换，这只有运算符重载可能做到。

#### 12.6.2.1 反身性

使用全局重载运算符而不用成员运算符的最便利的原因之一是在全局版本中的自动类型转换可以针对左右任一操作数，而成员版本必须保证左侧操作数已处千正确的形式。如果想两个操作数都被转换，全局版本可以节省很多代码。下面有一个小例子：

> 代码示例：
[C12_20_ReflexivityInOverloading.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/12.%20Operator%20Overloading/C12_20_ReflexivityInOverloading.cpp)

```C++
    // C12_20_ReflexivityInOverloading.cpp
    class Number
    {
        int i;
    public:
        Number(int ii = 0) : i(ii) {}
        const Number operator+(const Number& n) const
        {
            return Number(i + n.i);
        }
        friend const Number operator-(const Number&, const Number&);
    };

    const Number operator-(const Number& n1, const Number& n2)
    {
        return Number(n1.i - n2.i);
    }

    int main()
    {
        Number a(47), b(11);
        a + b;  // OK
        a + 1;  // 2nd arg converted to Number
        // 1 + a;  // Wrong, 1st arg not of type Number

        a - b;  // OK
        a - a;  // 2nd arg converted to Number
        1 - a;  // 1st arg converted to Number
    }
```

类`Number`有一个成员`operator+`和一个`friend operator-`。**因为有一个使用单一int参数的构造函数，在正确条件下，int可以自动转换为`Number`**。但当编译器看到一个`int`、一个+号和一个`Number`时，它就不知道如何去做，因为它所拥有的是`Number::operator+`，需要左侧的操作数是`Number`对象。因此，编译器发出一个出错信息。

对于`friend operator-`，情况就不同了。编译器需要填满两个参数，它不是限定`Number`作为左侧参数。因此，对于表达式`1 - a`，编译器就是用构造函数将第一个参数转换为`Number`。

有时也许想通过把它们设成成员函数来限定运算符的使用。例如当用一个矢量与矩阵相乘，矢量必须在右侧。但如果想让运算符转换任一个参数，就要使运算符为友元函数。

同时，编译器不会把表达式`1 - 1`的两个参数转换为`Number`对象。。编译器首先匹配“最简单的”可能性，对于表达式`1-1`将优先使用内置运算符。

### 12.6.3 类型转换例子

本例中的自动类型转换对于任一含有字符串的类是非常有帮助的。**如果不用自动类型转换就想从标准的C库函数中使用所有的字符串函数，那么就得为每一个函数写一个相应的成员函数**，就像下面的例子：

> 代码示例：
[C12_21_Strings1.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/12.%20Operator%20Overloading/C12_21_Strings1.cpp)

```C++
    // C12_21_Strings1.cpp
    // No auto tupe conversion
    #include "../require.h"
    #include <cstring>
    #include <cstdlib>
    #include <string>
    using namespace std;

    class Stringc
    {
        string s;
    public:
        Stringc(const string& str = "") : s(str) {}
        int strcmp(const Stringc& S) const
        {
            return ::strcmp(s.c_str(), S.s.c_str());
        }
    };

    int main()
    {
        Stringc s1("hello"), s2("there");
        s1.strcmp(s2);
    }
```

这里只写了一个`strcmp()`函数，但必须为可能需要的`<cstring>`中的每一个写一个相应的函数。幸运的是，可以提供一个允许访问`<cstring>`中所有函数的自动类型转换：

> 代码示例：
[C12_22_Strings2.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/12.%20Operator%20Overloading/C12_22_Strings2.cpp)

```C++
    // C12_22_Strings2.cpp
    // With auto type conversion
    #include "../require.h"
    #include <cstring>
    #include <cstdlib>
    #include <string>
    using namespace std;

    class Stringc
    {
        string s;
    public:
        Stringc(const string& str = "") : s(str) {}
        operator const char*() const 
        {
            return s.c_str();
        }
    };

    int main()
    {
        Stringc s1("hello"), s2("there");
        strcmp(s1, s2); // Standard C function
        strspn(s1, s2); // Any string function!
    }
```

因为编译器知道如何从`Stringc`转换到`char*`，所以现在任何一个接受`char*`参数的函数也可以接受`Stringc`参数。

### 12.6.4 自动类型转换的缺陷

因为编译器必须选择如何执行类型转换，所以如果没有正确地设计出转换，编译器会产生麻烦。类`X`可以用`operator Y()`将它本身转换到类`Y`，这是一个简单且明显的情况。如果类`Y`有一个单个参数为`X`的构造函数，这也表示同样的类型转换。现在编译器有两个从`X`到`Y`的转换方法，所以当发生转换时，编译器会产生一个不明确指示的出错信息：

> 代码示例：
[C12_23_TypeConversionAmbiguity.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/12.%20Operator%20Overloading/C12_23_TypeConversionAmbiguity.cpp)

```C++
    // C12_23_TypeConversionAmbiguity.cpp
    class Orange;   // Class declaration

    class Apple
    {
    public:
        operator Orange() const;    // Convert Apple to Orange
    };

    class Orange
    {
    public:
        Orange(Apple);  // Convert Apple to Orange
    };

    void f(Orange) {}

    int main()
    {
        Apple a;
        // 应用多个用户定义的从 "Apple" 到 "Orange" 的转换
        // f(a);   // Error: ambiguous conversion
    }
```

这个问题的解决方法是不要那样做，而是仅提供单一的从一个类型到另一个类型的自动转换方法。

当提供了转换到不止一种类型的自动转换时，会发生一个引起出错的更困难的问题。有时，这个问题被称为**扇出**(**fan-out**)。

> 代码示例：
[C12_24_TypeConversionFanout.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/12.%20Operator%20Overloading/C12_24_TypeConversionFanout.cpp)

```C++
    // C12_24_TypeConversionFanout.cpp
    class Orange {};
    class Pear {};

    class Apple 
    {
    public:
        operator Orange() const;
        operator Pear() const;
    };

    // Overloaded eat();
    void eat(Orange);
    void eat(Pear);

    int main()
    {
        Apple(c);
        // 有多个 重载函数 "eat" 实例与参数列表匹配:
        // eat(c); // Error: Apple->Orange or Apple->Pear？？？
    }
```

类`Apple`有向`Orange`和`Pear`的自动转换。这样存在一个隐藏的缺陷：使用了创建的两种版本的重载运算符`eat()`时就出现问题了。

通常，对于自动类型的解决方法是**只提供一个从某类型向另一个类型转换的自动转换版本**。当然也可以有多个向其他类型的转换，但它们不应该是自动转换，而应该用如`makeA()`和`makeB()`这样的名字来创建显式的函数调用。

#### 12.6.4.1 隐藏的行为

自动类型转换会引入比所希望的更多的潜在行为。下面要费点力去理解了，看看CopyingVsInitialization.cpp修改后的例子：

> 代码示例：
[C12_25_TypeConversionFanout2.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/12.%20Operator%20Overloading/C12_25_TypeConversionFanout2.cpp)

```C++
    // C12_25_TypeConversionFanout2.cpp
    class Fi {};

    class Fee
    {
    public:
        Fee(int){}
        Fee(const Fi&) {}
    };

    class Fo
    {
        int i;
    public:
        Fo(int x = 0) : i(x) {}
        operator Fee() const {return Fee(i);}
    };

    int main()
    {
        Fo fo;
        Fee fee = fo;
    }
```

这里没有从`Fo`对象创建`Fee fee`的构造函数。然而，`Fo`有一个到`Fee`的自动类型转换。这里也没有从`Fee`对象创建Fee的拷贝构造函数，但这是一种能由编译器帮助我们创建的特殊函数之一（默认的构造函数、拷贝构造函数、operator=和析构函数可自动创建）。

对于`Fee fee = fo;`自动类型转换运算符被调用并创建一个拷贝函数。

## 12.7 小结、

如果运算符重载对于类的设计者或类的使用者不能提供特别显著的益处，则最好不要使用，因为增加运算符重载会使问题混淆。