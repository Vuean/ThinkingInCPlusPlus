# 第9章 内联函数

**宏**(**macro**)的实现是用预处理器而不是编译器。在C++中，使用预处理器宏存在两个问题。第一个问题：宏看起来像一个函数调用，但并不总是这样。这样就隐藏了难以发现的错误。第二个问题是C++特有的：预处理器不允许访问类的成员数据。这意味着预处理器宏不能用作类的成员函数。

本章将介绍C++中预处理器宏存在的问题、在C++中如何用内联函数解决这些问题以及使用内联函数的方针和内联函数的工作机制。

## 9.1 预处理器的缺陷

预处理器宏存在问题的关键**是我们可能认为预处理器的行为和编译器的行为一样**。

考虑如下简单例子：`#define F (x) (x + 1)`，假如有一个F的调用：`F(1)`，预处理器展开它：`(x) (x + 1)(1)`，出现这个问题是因为在宏定义中`F`和括号之间存在空格。当这个空格取消后，调用宏时可以有空格空隙，如`F (1)`，依然可以正确地展开为：`(1 + 1)`。

这里存在两个问题。第一个问题是**表达式在宏内展开，所以它们的优先级不同于所期望的优先级**。例如：`#define FLOOR(x, b) x>=b?0:1`，但如果用表达式作参数：`if(FLOOR(a&0xf, 0x07))`，宏将展开为：`if(a&0x0f>=0x07>0:1)`，因为`&`的优先级比`>=`的低，所以宏的展开结果将与原本所期望的不一致。

可通过在宏定义内的各个地方使用括弧来解决：`#define FLOOR(x,b) ((x)>=(b)?0:1)`。

第二个问题：不像普通函数，**每次在宏中使用一个参数，都对这个参数求值**。只要使用普通变量调用宏仅，求值就无危险。但假如参数求值有副作用，那么结果可能出乎预料。

例如，下面这个宏决定它的参数是否在一定范围：`#define BAND(x) (((x)>5 && (x)<10) ? (x) : 0)`，只要使用一个“普通”参数，宏和真的函数的工作方式非常相似，但仍存在问题，例如：

> 代码示例：
[C9_01_MacroSideEffects.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/9.%20Inline%20Functions/C9_01_MacroSideEffects.cpp)

```C++
    // C9_01_MacroSideEffects.cpp
    #include "../require.h"
    #include <fstream>
    using namespace std;

    #define BAND(x) (((x)>5 && (x)<10) ? (x) : 0)

    int main()
    {
        ofstream out("macro.out");
        assure(out, "macro.out");
        for(int i = 4; i < 11; i++)
        {
            int a = i;
            out << "a = " << a << endl << '\t';
            out << "BAND(++a)=" << BAND(++a) << endl;
            out << "\t a = " << a << endl;
        }
    }
```

```C++
    输出：
    a = 4
    BAND(++a)=0
     a = 5
a = 5
    BAND(++a)=8
     a = 8
a = 6
    BAND(++a)=9
     a = 9
a = 7
    BAND(++a)=10
     a = 10
a = 8
    BAND(++a)=0
     a = 10
a = 9
    BAND(++a)=0
     a = 11
a = 10
    BAND(++a)=0
     a = 12
```

**宏命名常用大写字母**。当a等于4时，仅测试了条件表达式第一部分，表达式只求值—次，所以宏调用的副作用是a等于5。但当数字在值域范围内是，两个表达式都测试，产生两次自增操作。

### 9.1.1 宏和访问

预处理器只是简单地执行字符替代，所以不能用下面的形式写：

```C++
    class X
    {
        int i;
    public:
    #define VAL(X::i)   // Error
    };
```

另外，这里没有指明正在使用哪个对象。

## 9.2 内联函数

在C++中，宏的概念是作为**内联函数**(**inline function**)来实现的，而内联函数无论从那一方面上说都是真正的函数。内联函数能够像普通函数一样具有我们所有期望的任何行为。惟一不同之处是**内联函数在适当的地方像宏一样展开，所以不需要函数调用的开销**。

**任何在类中定义的函数自动地成为内联函数，但也可以在非类的函数前面加上inline关键字使之成为内联函数**。但为了使之有效，**必须使函数体和声明结合在一起**，否则，编译器将它作为普通函数对待。

因此，`inline int plusOne(int x);`，没有任何效果，仅仅只是声明函数，成功方法如下：`inline int plusOne(int x) {return ++x;}`。**编译器将检查函数参数列表使用是否正确，并返回值（进行必要的转换）**。

**一般应该把内联定义放在头文件里**。当编译器看到这个定义时，它把函数类型（函数名+返回值）和函数体放到符号表里。

### 9.2.1 类内部的内联函数

为了定义内联函数，通常必须在函数定义前面放一个`inline`关键字。但这在类内部定义内联函数时并不是必须的。任何在类内部定义的函数自动地成为内联函数。

> 代码示例：
[C9_02_Inline.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/9.%20Inline%20Functions/C9_02_Inline.cpp)

```C++
    // C9_02_Inline.cpp
    // Inline inside classes
    #include <iostream>
    #include <string>
    using namespace std;

    class Point
    {
        int i, j, k;
    public:
        Point() : i(0), j(0), k(0) {}
        Point(int ii, int jj, int kk) 
            : i(ii), j(jj), k(kk) {}
        void print(const string& msg = "") const
        {
            if(msg.size() != 0)
                cout << msg << endl;
            cout << "i = " << i << ", ";
            cout << "j = " << j << ", ";
            cout << "k = " << k << endl;
        }
    };

    int main()
    {
        Point p, q(1, 2, 3);
        p.print("value of p");
        q.print("value of q");
    }
```

两个构造函数和`print()`函数都默认为内联函数。不管函数是否是内联函数，惟一不同之处在于它们的效率不一样。

### 9.2.2 访问函数

在类中内联函数的最重要的使用之一是用做**访问函数**(**access function**)。这是一个小函数，它容许读或修改对象状态——即一个或几个内部变量。

> 代码示例：
[C9_03_Access.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/9.%20Inline%20Functions/C9_03_Access.cpp)

```C++
    // C9_03_Access.cpp
    // Inline access funtions
    #include <iostream>
    class Access
    {
        int i;
    public:
        int read() const { return i; }
        void set(int ii) { i = ii; }
    };

    int main()
    {
        Access A;
        A.set(100);
        int x = A.read();
        std::cout << x << std::endl;
    }
```

在上述例子中，类的状态变量设计为私有，对私有数据成员的访问只能通过成员函数接口进行。

#### 9.2.2.1 访问器和修改器

同时，访问函数又可以进一步地分为**访问器**(**accessor**)（用于从一个对象读状态信息）和**修改器**(**mutator**)（用于修改状态信息）。

> 代码示例：
[C9_04_Rectangle.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/9.%20Inline%20Functions/C9_04_Rectangle.cpp)

```C++
    // C9_04_Rectangle.cpp
    // Accessors & mutators

    class Rectangle
    {
        int wide, high;
    public:
        Rectangle(int w = 0, int h = 0)
            : wide(w), high(h){}
        int width() const { return wide; }
        void width(int w) { wide = w; }

        int height() const { return high; }
        void height(int h) { high = h; }
    };

    int main()
    {
        Rectangle r(19, 47);
        r.height(2 * r.width());
        r.width(2 * r.height());
    }
```

同时可以选用“get”和“set”来标识访问器和修改器。

> 代码示例：
[C9_05_Rectangle2.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/9.%20Inline%20Functions/C9_05_Rectangle2.cpp)

```C++
    // C9_05_Rectangle2.cpp

    class Rectangle
    {
        int width, height;
    public:
        Rectangle(int w = 0, int h = 0)
            : width(w), height(h){}
        int getWidth() const { return width; }
        void setWidth(int w) { width = w; }

        int getHeight() const { return height; }
        void setHeight(int h) { height = h; }
    };

    int main()
    {
        Rectangle r(19, 47);
        r.setHeight(2 * r.getWidth());
        r.setWidth(2 * r.getHeight());
    }
```

使用标准的C库函数的时间函数来生成简单的`Time`类：

> 代码示例：
[C9_06_Cpptime.h](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/9.%20Inline%20Functions/C9_06_Cpptime.h)

```C++
    // C09:Cpptime.h
    // A simple time class
    #ifndef CPPTIME_H
    #define CPPTIME_H
    #include <ctime>
    #include <cstring>

    class Time
    {
        std::time_t t;
        std::tm local;
        char asciiRep[26];
        unsigned char lflag, aflag;
        void updateLocal()
        {
            if(!lflag)
            {
                local = *std::localtime(&t);
                lflag++;
            }
        }
        void updateAscii()
        {
            if(!aflag)
            {
                updateLocal();
                std::strcpy(asciiRep, std::asctime(&local));
                aflag++;
            }
        }
    public:
        Time() { mark(); }
        void mark()
        {
            lflag = aflag = 0;
            std::time(&t);
        }
        const char* ascii()
        {
            updateAscii();
            return asciiRep;
        }
        // Difference in seconds:
        int delta(Time* dt) const
        {
            return int(std::difftime(t, dt->t));
        }
        int daylightSavings()
        {
            updateLocal();
            return local.tm_isdst;
        }
        int dayOfYear()
        {
            updateLocal();
            return local.tm_yday;
        }
        int dayOfWeek()
        {
            updateLocal() ;
            return local.tm_wday;
        }
        int since1900 () 
        { // Years since 1900
        updateLocal();
        return local.tm_year;
        }
        int month()
        { // Since January
            updateLocal() ;
            return local.tm_mon;
        }
        int dayOfMonth()
        {
            updateLocal();
            return local.tm_mday;
        }
        int hour()
        {
            updateLocal();
            return local.tm_hour;
        }
        int minute()
        {
            updateLocal();
            return local.tm_min;
        }
        int second()
        {
            updateLocal();
            return local.tm_sec;
        }
    };
    #endif // CPPTIME_H
```

`tm local`和ASCII字符表示法`asciiRep`都有一个标记来显示它们是否已被更新为当前的时间`time_t`。两个私有函数`updateLocal()`和
`updateAscii()`检查标记，并有条件地执行更新操作。

测试程序：

> 代码示例：
[C9_06_Cpptime.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/9.%20Inline%20Functions/C9_06_Cpptime.cpp)

```C++
    // C9_06_Cpptime.cpp
    #include "C9_06_Cpptime.h"
    #include <iostream>
    using namespace std;

    int main()
    {
        Time start;
        for(int i = 0; i < 1000; i++)
        {
            cout << i << ' ';
            if(i%10 == 0)
                cout << endl;
        }
        Time end;
        cout << endl;
        cout << "start = " << start.ascii();
        cout << "end = " << end.ascii();
        cout << "delta = " << end.delta(&start);
    }
```

## 9.3 带内联函数的Stash和Stack

引入了内联函数，现在，可以把`Stash`和`Stack`类变得更有效。

> 代码示例：
[C9_07_Stash4.h](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/9.%20Inline%20Functions/C9_07_Stash4.h)

```C++
    // C9_07_Stash4.h
    #ifndef STASH4_H
    #define STASH4_H
    #include "../require.h"

    class Stash
    {
        int size;
        int quantity;
        int next;
        // Dynamically allocated array of bytes:
        unsigned char* storage;
        void inflate(int increase);
    public:
        Stash(int sz) : size(sz), quantity(0), 
            next(0), storage(0) {}
        Stash(int sz, int initQuantity) : size(sz), quantity(0), 
            next(0), storage(0)
        {
            inflate(initQuantity);
        }
        Stash::~Stash()
        {
            if(storage != 0)
                delete []storage;
        }
        int add(void* element);
        void* fetch(int index) const
        {
            require(0 <= index, "Stash::fetch (-)index");
            if(index >= next)
                return 0;
            // produce pointer to desired element:
            return &(storage[index * size]);
        }
        int count() const {return next;}
    }

    #endif // STASH4_H
```

小函数作为内联函数工作是理想的，但要注意：两个最大的函数仍旧保留为非内联函数，因为要是把它们作为内联使用的话，很可能在性能上得不到什么改善。

> 代码示例：
[C9_07_Stash4.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/9.%20Inline%20Functions/C9_07_Stash4.cpp)

```C++
    // C9_07_Stash4.cpp
    #include "C9_07_Stash4.h"
    #include <iostream>
    #include <cassert>
    using namespace std;
    const int increment = 100;

    int Stash::add(void* element)
    {
        if(next >= quantity)    // Enough space left
            inflate(increment);
        // Copy element into storage starting at next empty space
        int startBytes = next * size;
        unsigned char* e = (unsigned char*)element;
        for(int i = 0; i < size; i++)
            storage[startBytes + i] = e[i];
        next++;
        return(next - 1);
    }

    void Stash::inflate(int increase)
    {
        assert(increase >= 0);
        if(increase == 0) return;
        int newQuantity = quantity + increase;
        int newBytes = newQuantity * size;
        int oldBytes = quantity * size;
        unsigned char* b = new unsigned char[newBytes];
        for(int i = 0; i < oldBytes; i++)
            b[i] = storage[i];
        delete [] storage;
        storage = b;
        quantity = newQuantity;
    }
```

测试程序：

> 代码示例：
[C9_08_StashTest.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/9.%20Inline%20Functions/C9_08_StashTest.cpp)

```C++
// C9_08_StashTest.cpp
# include "C9_07_Stash4.h"
# include "../require.h"
# include <fstream>
# include <iostream>
# include <string>
using namespace std;

int main()
{
    Stash intStash(sizeof(int)) ;
    for(int i = 0; i < 100; i++)
        intStash.add(&i) ;
    for (int j = 0; j < intStash.count() ; j++)
        cout << "intStash.fetch( " << j << ") = "
             << *(int*) intStash.fetch(j)
             << endl;
    const int bufsize = 80;
    Stash stringStash(sizeof(char) * bufsize, 100);
    ifstream in("Stash4Test.cpp");
    assure(in, "Stash4Test.cpp");
    string line;
    while(getline(in, line))
        stringStash.add((char*)line.c_str());
    int k = 0;
    char* cp;
    while((cp = (char*)stringStash.fetch(k++)) != 0)
        cout << "StringStash.fectch(" << k << ") = " << cp << endl;
}
```

## 9.4 内联函数和编译器

当调用一个内联函数时，编译器首先确保调用正确，即所有的参数类型必须满足：要么与函数参数表中的参数类型一样，要么编译器能够将其转换为正确类型，并且返回值在目标表达式里应该是正确类型或可改变为正确类型。

假如内联函数也是成员函数，对象的地址(`this`)就会被放入合适的地方，这个动作当然也是预处理器不能完成的。

### 9.4.1 限制

有两种编译器不能执行内联的情况。在这些情况下，它就像对非内联函数一样， 根据内联函数定义和为函数建立存储空间，简单地将其转换为函数的普通形式。

**假如函数太复杂，编译器将不能执行内联**。

**假如要显式地或隐式地取函数地址，编译器也不能执行内联**。因为这时编译器必须为函数代码分配内存从而产生一个函数的地址。

内联仅是编译器的一个建议，编译器不会被强迫内联任何代码。

### 9.4.2 向前引用

> 代码示例：
[C9_09_EvaluationOrder.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/9.%20Inline%20Functions/C9_09_EvaluationOrder.cpp)

```C++
    // C9_09_EvaluationOrder.cpp
    // Inline evaluation order

    class Forward
    {
        int i;
    public:
        Forward() : i(0) {}
        // Call to undeclared function
        int f() const {return g() + 1;}
        int g() const {return i;}
    };

    int main()
    {
        Forward frwd;
        frwd.f();
    }
```

函数`f()`调用`g()`，但此时还没有声明`g()`。这也能正常工作，因为C++语言规定：只有在类声明结束后，其中的内联函数才会被计算。

当然，如果`g()`反过来调用`f()`，就会产生递归调用，这对于编译器来说太复杂而不能执行内联。

### 9.4.3 在构造函数和析构函数里隐藏行为

构造函数和析构函数都可能隐藏行为，因为类可以包含子对象，子对象的构造函数和析构函数必须被调用。下面是一个带成员对象的例子：

> 代码示例：
[C9_10_Hidden.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/9.%20Inline%20Functions/C9_10_Hidden.cpp)

```C++
    // C9_10_Hidden.cpp
    // Hidden activities in inlines
    #include <iostream>
    using namespace std;

    class Member
    {
        int i, j, k;
    public:
        Member(int x = 0) : i(x), j(x), k(x) {}
        ~Member() {cout << "~Member()" << endl;}
    };

    class WithMembers
    {
        Member q, r, s;
        int i;
    public:
        WithMembers(int ii) : i(ii) {}
        ~WithMembers() {cout << "~WithMembers" << endl;}
    };

    int main()
    {
        WithMembers wm(1);
    }
```

成员对象`q`、`r`和`s`的构造函数和析构函数将被自动调用，这些构造函数和析构函数也是内联的，所以它们和普通的成员函数的差别是非常显著的。

## 9.5 减少混乱

使用关键字`inline`优化`Rectangle.cpp`：

> 代码示例：
[C9_11_Noinsitu.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/9.%20Inline%20Functions/C9_11_Noinsitu.cpp)

```C++
    // C9_11_Noinsitu.cpp
    // Removing in situ functions

    class Rectangle
    {
        int width, height;
    public:
        Rectangle(int w = 0, int h = 0);
        int getWidth() const;
        void setWidth(int w);
        int getHeight() const;
        void setHeight(int h);
    };

    inline Rectangle::Rectangle(int w, int h)
        : width(w), height(h) {}

    inline int Rectangle::getWidth() const { return width; }

    inline void Rectangle::setWidth(int w) { width = w; }

    inline int Rectangle::getHeight() const { return height; }

    inline void Rectangle::setHeight(int h) { height = h;}

    int main()
    {
        Rectangle r(19, 47);
        int iHeight = r.getHeight();
        r.setHeight(r.getWidth());
        r.setWidth(iHeight);
    }
```

## 9.6 预处理器的更多特征

几乎总是希望使用内联函数代替预处理器宏，但**字符串定义、字符串拼接和标志粘贴**例外。

字符串定义的完成是用`#`指示，它容许取一个标识符并把它转化为字符数组，然而字符串拼接在当两个相邻的字符串没有分隔符时发生，在这种情况下字符串组合在一起。如：`#define DEBUD(x) cout << #x " = "  << x << endl`。

上面的语句可以打印任何变量的值。也可以得到一个跟踪信息，在此信息里打印出它们执行的语句：`#define TRACE(s) cerr << #s << endl; s`。

`#s`将输出语句字符。第2个`s`重申了该语句，所以这个语句被执行。当然，这可能会产生问题，尤其是在一行`for`循环中。

```C++
    for(int i = 0; i < 100; i++)
        TRACE(f(i));
```

因为在`TRACE()`宏里实际上有两个语句，所以一行`for`循环只执行第一个。解决办法是`在宏中用逗号代替分号`。

### 9.6.1 标志粘贴

标志粘贴直接用`##`实现，在写代码时是非常有用的。**它允许设两个标识符并把它们粘贴在一起自动产生一个新的标识符**。

```C++
    #define FIELD(a) char* a++_string; int a##_size
    class Record
    {
        FIELD(one);
        FIELD(two);
        FIELD(three);
        // ...
    };
```

每次调用`FIELD()`宏，将产生一个保存字符数组的标识符和另一个保存字符数组长度的标识符。它不仅易读而且消除了编码出错，使维护更容易。

## 9.7 改进的错误检查

[require.h](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/require.h)

应该注意异常处理机制为处理各种错误提供了一种更加有效的方法，而不只是中止程序的运行。

## 9.8 小结

内联函数消除了预处理器宏和伴随的问题。通过用内联函数方式，成员函数可以和预处理器宏一样有效。
