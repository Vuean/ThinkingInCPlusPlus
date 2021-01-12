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

如果不用`using`指令，在这个名字空间的所有名字都需要被完全限定。`using`指令有一个缺点，那就是看起来不那么直观，引入名字的可见性的范围是在使用`using`的地方。

> 代码示例：
[C10_12_NamespaceOverriding1.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/10.%20Name%20Control/C10_12_NamespaceOverriding1.cpp)

```C++
    // C10_12_NamespaceOverriding1.cpp
    #include "C10_10_NameSpaceMath.h"
    int main()
    {
        using namespace Math;
        Integer a;  // Hide Math::a
        a.setSign(negative);
        // Now scope resolution is necessary to select Math::a
        Math::a.setSign(positive);
    }
```

如果有第二个名字空间，它包含了名字空间`Math`的某些名字：

> 代码示例：
[C10_12_NamespaceOverriding2.h](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/10.%20Name%20Control/C10_12_NamespaceOverriding2.h)

```C++
    // C10_12_NamespaceOverriding2.h
    #ifndef NAMESPACEOVERRING2_H
    #define NAMESPACEOVERRING2_H
    #include "C10_10_NameSpaceMath.h"
    namespace Calculation
    {
        using namespace Int;
        Integer divide(Integer, Integer);
    }
    #endif // NAMESPACEOVERRING2_H
```

因为这个名字空间也是用`using`指令来引人的，这样就可能产生冲突。不过，这种二义性出现在名字的使用时，而不是在`using`指令使用时。

> 代码示例：
[C10_13_OverridingAmbiguity.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/10.%20Name%20Control/C10_13_OverridingAmbiguity.cpp)

```C++
    // C10_13_OverridingAmbiguity.cpp
    #include "C10_10_NameSpaceMath.h"
    #include "C10_12_NamespaceOverriding2.h"
    void s()
    {
        using namespace Math;
        using namespace Calculation;
        // Everything is OK until
        divide(1, 2);   // Ambiguity
    }
    int main() { }
```

#### 10.2.2.3 使用声明

可以用**使用声明**(**using declaration**)一次性引人名字到当前范围内。**using声明**是在当前范围之内进行的一个声明，这就意味着在这个范围内它可以不顾来自`using`指令的名字。

> 代码示例：
[C10_14_UsingDeclaration.h](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/10.%20Name%20Control/C10_14_UsingDeclaration.h)

```C++
    // C10_14_UsingDeclaration.h
    #ifndef USINGDECLARATION_H
    #define USINGDECLARATION_H
    namespace U{
        inline void f() {}
        inline void g() {}
    }
    namespace V{
        inline void f() {}
        inline void g() {}
    }
    #endif // USINGDECLARATION_H
```

> 代码示例：
[C10_14_UsingDeclaration1.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/10.%20Name%20Control/C10_14_UsingDeclaration1.cpp)

```C++
    // C10_14_UsingDeclaration1.cpp
    #include "C10_14_UsingDeclaration.h"
    void h()
    {
        using namespace U;  // Using directive
        using V::f;   // Using declaration
        f();    // Calls V::f();
        U::f(); // Must fully quality to call
    }
```

`using`声明给出了标识符的完整的名字，但没有了类型方面的信息。`using`声明可以引起一个函数用相同的参数类型来重载。

`using`声明也可以出现在一个名字空间内，其作用与在其他地方时一样：

> 代码示例：
[C10_15_UsingDeclaration2.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/10.%20Name%20Control/C10_15_UsingDeclaration2.cpp)

```C++
    // C10_15_UsingDeclaration2.cpp
    #include "C10_14_UsingDeclaration.h"
    namespace Q
    {
        using U::f;
        using V::g;
    }

    void m()
    {
        using namespace Q;
        f();    // Calls U::f()
        g();    // Calls V::g()
    }
    int main() {}
```

一个`using`声明是一个别名，它允许在不同的名字空间声明同样的函数。如果不想由于引入不同名字空间而导致重复定义一个函数时，可以使用`using`声明，它不会引起任何二义性和重复。

### 10.2.3 名字空间的使用

当引入一个全局`using`指令时（可以在任何范围之外通过使用`using namespace`)，就已经为那个文件打开了该名字空间。在头文件中，最好使用明确的限定或者被限定在一定范围内的`using`指令和`using`声明。

## 10.3 C++中的静态成员

有时需要为某个类的所有对象分配一个单一的存储空间，实现将一个数据当成全局变量那样去存储， 但又被隐藏在类的内部，这一点可以用类的静态数据成员来实现。

类的静态成员拥有一块单独的存储区，而不管创建了多少个该类的对象。所有的这些对象的静态数据成员都共享这一块静态存储空间，这就为这些对象提供了一种互相通信的方法。但静态数据属于类，它的名字只在类的范围内有效，并且可以是`public`、`private`或者`protected`。

### 10.3.1 定义静态数据成员的存储

因为类的静态数据成员有着单一的存储空间而不管产生了多少个对象，所以**存储空间必须在一个单独的地方定义**。如果一个静态数据成员被声明但没有定义时，连接器会报告一个错误。

定义必须出现在类的外部（不允许内联）而且只能定义一次，因此它通常放在一个类的实现文件中。

```C++
    class A{
        static int i;
    public:
        // ..
    };
```

之后，必须在定义文件中为静态数据成员定义存储区：`int A::i = 1;`。

静态成员的初始化表达式是在一个类的作用域内，请看下例：

> 代码示例：
[C10_16_Statinit.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/10.%20Name%20Control/C10_16_Statinit.cpp)

```C++
    // C10_16_Statinit.cpp
    // Scope of static initializer
    #include <iostream>
    using namespace std;

    int x = 100;

    class WithStatic{
        static int x;
        static int y;
    public:
        void print() const
        {
            cout << "WithStatic::x = " << x << endl;
            cout << "WithStatic::y = " << y << endl;
        }
    };

    int WithStatic::x = 1;
    int WithStatic::y = x + 1;

    int main()
    {
        WithStatic ws;
        ws.print();
    }
```

这里，`withStatic::`限定符把`withStatic`的作用域扩展到全部定义中。

#### 10.3.1.1 静态数组的初始化

> 代码示例：
[C10_17_StaticArray.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/10.%20Name%20Control/C10_17_StaticArray.cpp)

```C++
    // C10_17_StaticArray.cpp
    // Initializing static arrays in classes
    class Values 
    {
        // static consts are initialized in-place:
        static const int scSize = 100;
        static const long scLong = 100;
        // Automatic counting works with static arrays.
        // Arrays, Non-integral and non-const statics
        // must be initialized externally:
        static const int scInts [];
        static const long scLongs [];
        static const float scTable[] ;
        static const char scLetters [];
        static int size;
        static const float scFloat;
        static float table[];
        static char letters[];
    };

    int Values:: size = 100;
    const float Values:: scFloat = 1.1;
    const int Values::scInts[] = 
    {
        99, 47, 33, 11, 7
    };

    const long Values::scLongs[] = 
    {
        99, 47, 33, 11, 7
    };

    const float Values::scTable[] = 
    {
        1.1, 2.2, 3.3, 4.4
    };

    const char Values::scLetters[]= 
    {
        'a', 'b', 'c', 'd', 'e',
        'f' , 'g' , 'h','i', 'j'
    };

    float Values::table[4] = 
    {
        1.1, 2.2, 3.3, 4.4
    };

    char Values::letters[10] = 
    {
        'a', 'b', 'c', 'd', 'e',
        'f', 'g', 'h', 'i', 'j '
    };

    int main ( ) { Values v; }
```

也可以创建类的静态常量对象和这样的对象的数组。

> 代码示例：
[C10_18_StaticObjectArrays.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/10.%20Name%20Control/C10_18_StaticObjectArrays.cpp)

```C++
    // C10_18_StaticObjectArrays.cpp
    // Static arrays of class objects
    class X
    {
        int i;
    public:
        X(int ii) : i(ii) {}
    };

    class Stat
    {
        // This doesn't work, although you might want it to:
        // static const X x (100) ;
        // Both const and non-const static class
        // objects must be initialized externally:
        static X x2;
        static X xTable2[];
        static const X x3;
        static const X xTable3[];
    };

    X Stat::x2(100);

    X Stat::xTable2[] = {
        X(1), X(2), X(3), X(4)
    };

    const X Stat::x3(100);

    const X Stat::xTable3[] = {
        X(1), X(2), X(3), X(4)
    };

    int main() {}
```

类对象的常量和非常量静态数组的初始化必须以相同的方式执行，它们遵守典型的静态定义语法。

### 10.3.2 嵌套类和局部类

可以很容易地把一个静态数据成员放在另一个类的嵌套类中。然而不能在局部类（在函数内部定义的类）中有静态数据成员。

> 代码示例：
[C10_19_Local.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/10.%20Name%20Control/C10_19_Local.cpp)

```C++
    // C10_19_Local.cpp
    // Static members & local classes
    #include <iostream>
    using namespace std;

    // Mested class CAN have static data members:
    class Outer
    {
        class Inner{
            static int i;   // ok
        };
    };

    int Outer::Inner::i = 47;

    // Local class cannot have static data members:
    void f()
    {
        class Local{
        public:
            // static int i;    // Error
        } x;
    }
    int main() { Outer x; f();}
```

### 10.3.3 静态成员函数

也可以创建一个静态成员函数，它为类的全体对象服务而不是为一个类的特殊对象服务。当产生一个静态成员函数时，也就表达了与一个特定类的联系。

可以用普通的方法调用静态成员函数，用点`.`和箭头`->`把它与一个对象相联系。然而，调用静态成员函数的一个更典型的方法是自我调用，这不需要任何具体的对象，而是像下面使用作用域运算符：

> 代码示例：
[C10_20_SimpleStaticMemberFunction.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/10.%20Name%20Control/C10_20_SimpleStaticMemberFunction.cpp)

```C++
    // C10_20_SimpleStaticMemberFunction.cpp
    class X
    {
    public:
        static void f() {}
    };

    int main()
    {
        X::f();
    }
```

当在一个类中看到静态成员函数时，要记住：**类的设让者是想把这些函数与整个类在概念上关联起来**。

**静态成员函数不能访问一般的数据成员，而只能访问静态数据成员，也只能调用其他的静态成员函数**。通常，当前对象的地址(`this`)是被隐式地传递到被调用的函数的。但一个静态成员函数没有`this`，所以它无法访问一般的成员。

对于数据成员来说，`static`关键字指定它对类的所有对象来说，都只占有相同的一块存储空间。与定义对象的静态使用相对应，静态函数意味着对这个函数的所有调用来说，一个局部变批只有一份拷贝。

> 代码示例：
[C10_21_StaticMemberFunctions.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/10.%20Name%20Control/C10_21_StaticMemberFunctions.cpp)

```C++
    // C10_21_StaticMemberFunctions.cpp
    class X
    {
        int i;
        static int j;
    public:
        X(int ii = 0) : i(ii)
        {
            // Non-static member function can access
            // static member function or data:
            j = i;
        }
        int val() const { return i; }
        static int incr()
        {
            // i++; // Error: static member function
            // cannot access non-static member data
            return ++j;
        }
        static int f()
        {
            // 静态成员必须于特性对象相对
            // Error: static member function cannot access 
            // non-static member function
            // val();
            return incr();
        }
    };

    int X::j = 0;
    int main()
    {
        X x;
        X* xp = &x;
        x.f();
        xp->f();
        X::f(); // Only works with static members`
    }
```

因为静态成员函数没有`this`指针，所以它既不能访问非静态的数据成员，也不能调用非静态的成员函数。

因为静态成员对象的初始化方法，所以可以把上述类的一个静态数据成员放到那个类的内部。下面是一个例子，它把构造函数变成私有的，这样Egg类只有一个惟一的对象存在，可以访问那个对象，但不能产生任何新的Egg对象。

> 代码示例：
[C10_22_Singleton.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/10.%20Name%20Control/C10_22_Singleton.cpp)

```C++
    // C10_22_Singleton.cpp
    // Static member of same type, ensures that only one object
    // of this type exists.
    // Also referred to as the "Singleton" pattern
    #include <iostream>
    using namespace std;

    class Egg
    {
        static Egg e;
        int i;
        Egg(int ii) : i(ii) {}
        Egg(const Egg&);
    public:
        static Egg* instance() {return &e;}
        int val() const {return i;}
    };

    Egg Egg::e(47);

    int main()
    {
        // Error -- can't create an Egg
        // You can access the single instance:
        // Egg x(1);
        cout << Egg::instance()->val() << endl;
    }
```

`E`的初始化出现在类的声明完成后，所以编译器已有足够的信息为对象分配空间并调用构造函数。

为了完全防止创建其他对象，还需要再做如下的工作：增加一个叫做**拷贝构造函数**(**copy constructor**)的私有构造函数。否则，可以通过拷贝构造函数创建一个`Egg`对象：

```C++
    Egg e = *Egg::instance();
    Egg e2(*Egg::instance());
```

## 10.4 静态初始化的相依性

对于作用域为多个翻译单元的静态对象来说，不能保证严格的初始化顺序，也没有办法来指定这种顺序。。下面的例子如果包含一个文件就会立即引起灾难：

```C++
    // First file
    #include <fstream>
    std::ofstream out("out.txt");
```

另一个文件在它的初始表达式之一中用到了`out`对象：

```C++
    // Second file
    #include <fstream>
    extern std::ofstream out;
    class Oof{
    public:
        Oof() {std::cout << "ouch";}
    } oof;
```

这个程序可能运行，也可能不能运行。如果在建立可执行文件时第一个文件先初始化，那么就不会有问题，但如果第二个文件先初始化，`Oof`的构造函数依赖于`out`的存在，而此时`out`还没有创建，于是就会引起混乱。

这种情况只会在相互依赖的静态对象的初始化时出现。在一个翻译单元内的一个函数的第一次调用之前，但在进入`main()`之后，这个翻译单元内的静态对象都被初始化。如果静态对象位于不同的文件中，则不能确定这些静态对象的初始化顺序。

另一个例子，在一个文件中：

```C++
    extern int y;
    int x = y + 1;
```

在另一个文件中：

```C++
    extern int x;
    int y = x + 1;
```

如果文件按上面的顺序被初始化，`y`开始被初始化为零，所以`x`变成1, 而后`y`被动态初始化为2。然而，如果初始化的顺序颠倒过来，`x`被静态初始化为零，`y`被初始化为1，而后`x`被初始化为2。

### 10.4.1 怎么办

有三种方法来处理这一问题：
    l) 不用它，避免初始化时的互相依赖。这是最好的解决方法。
    2) 如果需要用，就把那些关键的静态对象的定义放在一个文件中，这样只要让它们在文件中顺序正确就可以保证它们正确的初始化。
    3) 如果确信把静态对象放在几个不同的翻译单元中是不可避免的——如在编写一个库时，这时无法控制那些使用该库的程序员——这可以通过两种程序设计技术加以解决。

#### 10.4.1.1 技术一

该要求在库头文件中加上一个额外的类。这个类负责库中的静态对象的动态初始化。

> 代码示例：
[C10_23_Initializer.h](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/10.%20Name%20Control/C10_23_Initializer.h)

```C++
    // C10_23_Initializer.h
    // Static initialization technique
    #ifndef INITIALIZER_H
    #define INITIALIZER_H
    #include <iostream>
    extern int x; // Declarations, not definitions
    extern int y;

    class Initializer 
    {
        static int initCount;
    public:
        Initializer()
        {
            std::cout << "Initializer() " << std::endl;
            // Initialize first time only
            if (initCount++ == 0)
            {
                std::cout << "performing initialization" << std::endl;
            }
            x = 100;
            y = 200;
        }
        ~Initializer() 
        {
            std::cout << "~Initializer()" << std::endl;
            // Clean up last time only
            if(--initCount == 0)
                std::cout << "performing cleanup" << std::endl;
            // Any necessary cleanup heer
        }
    };
    // The following creates one object in each
    // file where I nitializer.h is included, but that
    // object is only visible within that file:
    static Initializer init;
    #endif // INITIALIZER_H
```

`x`、`y`的声明只是表明这些对象的存在，并没有为它们分配存储空间。然而`initializer init`的定义为每个包含此头文件的文件分配那些对象的存储空间，因为名字是`static`的它只在本翻译单元可见，所以连接器不会报告一个多重定义错误。

下面是一个包含`x`、`y`和`init_Count`定义的文件：

```C++
    // Definitions for Initializer.h
    #include "Initializer.h"
    // Static initialization will force all these values to zero:
    int x;
    int y;
    int Initializer::initCount;
```

这个例子用内部类型作为全局静态对象，这种方法也可以用于类，但其对象必须用`initializer`类动态初始化。一种方法就是创建一个没有构造函数和析构函数的类，而是带有不同名字的用于初始化和清除的成员函数。当然更常用的做法是在`initializer()`函数中，设定有指向对象的指针，用`new`创建它们。

#### 10.4.1.2 技术二

函数内部的静态对象在函数第一次被调用时初始化，且只被初始化一次。

## 10.5 替代连接说明

为实现在C++中使用C的库，C++提供了一个**替代连接说明**(**alternate linkage specification**)，它是通过重载`extern`关键字来实现的。`extern`后跟一个字符串来指定想声明的函数的连接类型，后面是函数声明。`extern "C" float f(int a, int b);`

这里告诉编译器`f()`是C连接，这样就不会转换函数名。

## 10.6 小结

`static`关键字很容易使人糊涂，因为有时它控制存储分配，而有时控制一个名字的可见性和连接。

在类的内部使用`static`是在全程序中控制名字的另一种方法。这些名字不会与全局名冲突，并且可见性和访问也限制在程序内部，使得在维护代码时能有更多的控制。
