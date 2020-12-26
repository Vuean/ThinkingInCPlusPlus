# 第10章 名字控制

C++允许我们对名字的产生和名字的可见性进行控制，包括这些名字的存储位置以及名字的连接。关于`static`的所有使用最基本的概念是指“位置不变的某个东西”，不管这里是指在内存中的物理位置还是指在文件中的可见性。

在本章里，我们将看到`static`如何控制存储和可见性，还将看到一种通过C++的**名字空间**特征来控制访问名字的改进方法。

## 10.1 来自C语言中的静态元素

在C和C++中，`static`都有两种基本的含义，并且这两种含义经常是互相冲突的：

1) 在固定的地址上进行存储分配，也就是说对象是在一个特殊的**静态数据区**(**static data area**)上创建的，而不是每次函数调用时在堆栈上产生的。这也是静态存储的概念。
2) 对一个特定的编译单位来说是局部的。这样，`static`控制名字的**可见性**(**visibility**)，所以这个名字在这个单元或类之外是不可见的。这也描述了连接的概念，它决定连接器将看到哪些名字。

### 10.1.1 函数内部的静态变量

通常，在函数体内定义一个局部变最时，编译器在每次函数调用时使堆栈的指针向下移一个适当的位置，为这些局部变量分配内存。有时想在两次函数调用之间保留一个变量的值，可以在函数内部定义一个`static`对象，这个对象将存储在程序的静态数据区中，而不是堆栈中。这个变量**只在函数第一次调用时初始化一次**，以后它将在两次函数调用之间保持它的值。

> 代码示例：
[C10_01_StaticVAriablesInFunctions.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/10.%20Name%20Control/C10_01_StaticVAriablesInFunctions.cpp)

```C++
    // C10_01_StaticVAriablesInFunctions.cpp
    #include "../require.h"
    #include <iostream>
    using namespace std;

    char oneChar(const char* charArray = 0)
    {
        static const char* s;
        if(charArray)
        {
            s = charArray;
            return *s;
        }
        else
        {
            require(s, "un-initialized s");
        }
        if(*s == '\0')
            return 0;
        return *s++;
    }

    char* a = "abcdefghijklmnopqrstuvwxyz";

    int main()
    {
        oneChar(a); // initializes s to a 
        char c;
        while((c = oneChar()) != 0)
            cout << c << endl;
    }
```

`static char* s`在每次`onechar()`调用时保留它的值，因为它存放在程序的静态数据区而不是存储在函数的堆栈中。当用一个字符指针作参数(`char*`）调用`oneChar()`时，参数值被赋给`s`，然后返回字符串的第一个字符。以后每次调用`oneChar()`都不用带参数，函数将使用默认参数`charArray`的默认值0，函数就会继续用以前初始化的`s`值取字符，直到它到达字符串的结尾标志——空字符为止，到这时，字符指针就不会再增加了，这样，指针不会越过字符串的末尾。

但是如果调用`oneChar()`时没有参数而且`s`以前没有初始化，那应该在定义`s`时提供一个初始值：`static char* s = 0`。

但如果没有为一个内部类型的静态变量提供一个初始值的话，编译器也会确保在程序开始时它被初始化为零（转化为适当的类型），所以在`oneChar()`中，函数第一次调用时`s`将被赋值为零，这样`if(!s)`后面的程序就会被执行。

上面的函数很容易产生多线程问题；无论什么时候设计一个包含静态变量的函数时，都应该记住多线程问题。

#### 10.1.1.1 函数内部的静态对象

零赋值只对内部类型有效，**用户自定义类型必须用构造函数来初始化**。因此，如果在定义一个静态对象时没有指定构造函数参数，这个类就必须有默认的构造函数。

> 代码示例：
[C10_02_StaticObjectsInFunction.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/10.%20Name%20Control/C10_02_StaticObjectsInFunction.cpp)

```C++
    // C10_02_StaticObjectsInFunction.cpp
    #include <iostream>
    using namespace std;

    class X
    {
        int i;
    public:
        X(int ii = 0) : i(ii) {}    // default
        ~X() {cout << "X::~X()" << endl;}
    };

    void f()
    {
        static X x1(47);
        static X x2;    // Default constructor required
    }

    int main()
    {
        f();
    }
```

在函数`f()`内部定义一个静态的X类型的对象，它可以用带参数的构造函数来初始化，也可以用默认构造函数。

#### 10.1.1.2 静态对象的析构函数

静态对象的析构函数在程序`从main()`中退出时，或者标准的C库函数`exit()`被调用时才被调用。如果用标准的C库函数`abort()`来退出程序，静态对象的析构函数并不会被调用。

同普通对象的销毁一样，静态对象的销毁也是按与初始化时相反的顺序进行的。全局对象总是在`main()`执行之前被创建，在退出`main()`时销毁。

> 代码示例：
[C10_03_StaticDestructors.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/10.%20Name%20Control/C10_03_StaticDestructors.cpp)

```C++
    // C10_03_StaticDestructors.cpp
    // Static object destructors
    #include <fstream>
    using namespace std;
    ofstream out("statdest.out");

    class Obj
    {
        char c; // Identifier
    public:
        Obj(char cc) : c(cc) 
        {
            out << "Obj::Obj() for " << c << endl;
        }
        ~Obj()
        {
            out << "Obj::~Obj() for " << c << endl;
        }
    };

    Obj a('a'); // Global (static storage)
    // Constructor & destructor always called

    void f()
    {
        static Obj b('b');
    }

    void g()
    {
        Obj c('c');
    }

    int main()
    {
        out << "inside main()" << endl;
        f();    // Calls static constructor for b
        g();
        out << "leaving main()" << endl;
    }
```

`Obj a`是一个全局的`Obj`类的对象，所以构造函数总是在`main()`函数之前就被调用。函数`f()`内的`Obj`类的静态对象`b`和函数`g()`内的对象`c`的构造函数只在这些函数被调用时才起作用。

当退出`main()`函数时，所有被创建的对象的析构函数按创建时相反的顺序被调用。

跟踪文件`ofstream`的对象`out`也是一个静态对象，因为它定义在所有函数之外，位于静态存储区。

在C++中，全局静态对象的构造函数是在`main()`之前调用的，所以现在有了一个在进人`main()`之前执行一段代码的简单的、可移植的方法，并且可以在退出`main()`之后用析构函数执行代码。

### 10.1.2 控制连接

一般情况下，在**文件作用域**(**file scope**)内的所有名字（不嵌套在类或函数中的名字）对程序中的所有翻译单元来说都是可见的。这就是所谓的**外部连接**(**external linkage**)，因为在连接时这个名字对连接器来说是可见的，对单独的翻译单元来说，它是外部的。全局变量和普通函数都有外部连接。

在文件作用域内，一个被声明为`static`的对象或函数的名字对翻译单元（即出现声明的.cpp文件）来说是局部于该单元的，这些名字有**内部连接**(**internal linkage**)。这意味着可以在其他的翻译单元中使用同样的名字，而不会发生名字冲突。

内部连接的一个好处是这个名字可以放在一个头文件中而不用担心连接时发生冲突。

#### 10.1.2.1 冲突问题

所有的全局对象都是隐含为静态存储的，所以如果定义：`int a = 0;`，则`a`被存储在程序的静态数据区，在进入`main()`函数之前，`a`即已经被初始化了。`a`对所有的翻译单元都是全局可见的。

`static`（只在翻译单元内可见）的反义是`extern`，它明确地声明了这个名字对所有翻译单元都是可见的。所以`int a = 0`定义与`extern int a = 0;`相同。

而`static int a = 0;`，使得`a`成了一个内部连接，但存储类型没有改变——对象总是驻留在静态数据区，而不管是`static`还是`extern`。一旦进入局部变量，`static`就不会再改变变量的可见性（这时`extern`是没有意义的），而只是改变变量的存储类型。

如果把局部变量声明为`extern`，这意味着某处已存在一个存储区（所以该变量对函数来说实际上是全局的）：

> 代码示例：
[C10_04_LocalExtern.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/10.%20Name%20Control/C10_04_LocalExtern.cpp)

```C++
    // C10_04_LocalExtern.cpp
    // {L} LocalExtern2
    #include <iostream>

    int main()
    {
        extern int i;
        std::cout << i;
    }
```

> 代码示例：
[C10_04_LocalExtern2.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/10.%20Name%20Control/C10_04_LocalExtern2.cpp)

```C++
    // C10_04_LocalExtern2.cpp {O}
    int i = 5;
```

对函数名（非成员函数），`static`和`extern`只会改变它们的可见性，所以如果说：`extern void f();`，它和没有修饰时的声明是一样的：`void f();`，如果定义`static void f();`，则意味着`f()`只在本翻译单元内是可见的，这称作**文件静态**(**file static**)。

### 10.1.3 其他存储类型说明符

`auto`指明编译器自动为该变量分配存储空间的方法。还有一个是`register`，它说明的也是局部(auto)变量，但它告诉编译器这个特殊的变量要经常用到，所以编译器应该尽可能地让它保存在寄存器中。

## 10.2 名字空间

虽然名字可以嵌套在类中，但全局函数、全局变量以及类的名字还是在同一个全局名字空间中。

可以用C++的**名字空间**(**namespace**)特征，把一个全局名字空间分成多个可管理的小空间。关键字`namespace`，如同`class`、`struct`、`enum`和`union`一样，把它们的成员的名字放到了不同的空间中去，尽管其他的关键字有其他的目的，但`namespace`惟一的目的是产生一个新的名字空间。

### 10.2.1 创建一个名字空间

创建一个名字空间与创建一个类非常相似：

> 代码示例：

```C++
    // C10_MyLib.cpp
    namespace MyLib
    {
        // Declaration
    };
    int main() {}
```

这就产生了一个新的名字空间，其中包含了各种声明。然而，`namespace`与`class`、`struct`、`union`和`enum`有着明显的区别：

* `namespace`只能在全局范围内定义，但它们之间可以互相嵌套；
* 在`namespace`定义的结尾，右花括号的后面不必跟一个分号；
* 一个`namespace`可以在多个头文件中用一个标识符来表示，就好像重复定义一个类一样。

> 代码示例：
[C10_05_Header.h](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/10.%20Name%20Control/C10_05_Header.h)

```C++
    // C10_05_Header.h
    #ifndef HEADER1_H
    #define HEADER1_H
    namespace MyLib{
        extern int x;
        void f();
    }
    #endif // HEADER1_H
```

> 代码示例：
[C10_05_Header2.h](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/10.%20Name%20Control/C10_05_Header.h)

```C++
    // C10_05_Header2.h
    #ifndef HEADER2_H
    #define HEADER2_H
    #include "C10_05_Header.h"
    // Add more names to MyLib
    namespace MyLib {
        extern int y;
        void g();
    }
    #endif // HEADER2_H
```

```C++
    // C10: Continueation.cpp
    #include "C10_05_Header2.h"
    int main() {}
```

* 一个`namespace`的名字可以用另一个名字来作它的别名，这样就不必敲打那些开发商提供的冗长的名字了。

```C++
    // C10: BobsSuperDuperLibrary.cpp
    namespace BobsSuperDuperLibrary{
        class Widge{ };
        class Poppit { };
    }
    // Todo much to type
    namespace Bob = BobsSuperDuperLibrary;
    int main() {}
```

* 不能像类那样去创建一个名字空间的实例。

#### 10.2.1.1 未命名的名字空间

每个翻译单元都可包含一个未命名的名字空间——可以不用标识符而只用`namespace`增加一个名字空间。

> 代码示例：
[C10_06_UnnamedNamespaces.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/10.%20Name%20Control/C10_06_UnnamedNamespaces.cpp)

```C++
    // C10_06_UnnamedNamespaces.cpp
    namespace{
        class Arm { };
        class Leg { };
        class Head { };
        class Robot{
            Arm arm[4];
            Leg leg[16];
            Head head[3];
        } xanthan;
        int i, j, k;
    }

    int main() {}
```

在这个空间中的名字自动地在翻译单元内无限制地有效。但要确保每个翻译单元只有一个未命名的名字空间。如果把一个局部名字放在一个未命名的名字空间中，不需要加上`static`说明就可以让它们作内部连接。

#### 10.2.1.2 友元

可以在一个名字空间的类定义之内**插入**(**inject**)一个**友元**(**friend**)声明：

> 代码示例：
[C10_07_FriendInjection.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/10.%20Name%20Control/C10_07_FriendInjection.cpp)

```C++
    // C10_07_FriendInjection.cpp
    namespace Me
    {
        class Us{
            friend void you();
        };
    }
    int main() {}
```

这样函数`you()`就成了名字空间`Me`的一个成员。

### 10.2.2 使用名字空间

在一个名字空间中引用一个名字可以采取三种方法：第一种方法是**用作用域运算符**；第二种方法是**用`using`指令把所有名字引入到名字空间中**；第三种方法是**用`using`声明一次性引用名字**。

> 代码示例：
[C10_08_ScopeResolution.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/10.%20Name%20Control/C10_08_ScopeResolution.cpp)

```C++
    // C10_08_ScopeResolution.cpp
    namespace X
    {
        class Y
        {
            static int i;
        public:
            void f();
        };
        class Z;
        void func();
    }

    int X::Y::i = 9;
    class X::Z
    {
        int u, v, w;
    public:
        Z(int i);
        int g();
    };

    X::Z::Z(int i)
    {
        u = v = w = i;
    }

    int X::Z::g() {return u = v = w = 0;}


    void Xfunc()
    {
        X::Z a(1);
        a.g();
    }

    int main() {}
```

注意定义`X::Y::i`就像引用一个类`Y`的数据成员一样容易，`Y`如同被嵌套在类`X`中而不像是被嵌套在名字空间`X`中。

#### 10.2.2.2 使用指令

用`using`关键字可以让我们立即进入整个名字空间，这种`using`和`namespace`关键字的搭配使用称为**使用指令**(**using directive**)。

> 代码示例：
[C10_09_NameSpaceInt.h](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/10.%20Name%20Control/C10_09_NameSpaceInt.h)

```C++
    // C10_09_NameSpaceInt.h
    #ifndef NAMESPACEINT_H
    #define NAMESPACEINT_H
    namespace Int
    {
        enum sign{positive, negative};
        class Integer
        {
            int i;
            sign s;
        public:
            Integer(int ii = 0)
                : i(ii),
                s(i >= 0 ? positive : negative)
            {}
            sign getSign() const { return s; }
            void setSign(sign sgn) {s = sgn;}
        };
    }
    #endif // NAMESPACEINT_H
```

`using`指令的用途之一就是把名字空间`Int`中的所有名字引入到另一个名字空间中，让这些名字嵌套在那个名字空间中。

> 代码示例：
[C10_10_NameSpaceMath.h](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/10.%20Name%20Control/C10_10_NameSpaceMath.h)

```C++
    // C10_10_NameSpaceMath.h
    #ifndef NAMESPACEMATH_H
    #define NAMESPACEMATH_H
    #include "C10_09_NameSpaceInt.h"
    namespace Math{
        using namespace Int;
        Integer a, b;
        Integer divide(Integer, Integer);
    }
    #endif // NAMESPACEMATH_H
```

可以在一个函数中声明名字空间`Int`中的所有名字，但是让这些名字嵌套在这个函数中。

> 代码示例：
[C10_11_Arithmetic.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/10.%20Name%20Control/C10_11_Arithmetic.cpp)

```C++
    // C10_11_Arithmetic.cpp
    #include "C10_09_NameSpaceInt.h"
    void arithmetic()
    {
        using namespace Int;
        Integer x;
        x.setSign(positive);
    }
    int main() {}
```

