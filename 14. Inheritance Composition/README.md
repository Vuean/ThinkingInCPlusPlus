# 第14章 继承和组合

C++最重要的特征之一是代码重用。在本章中，我们将看到两种完成这项
任务的方法。第一种方法很直接：我们简单地在新类中创建已存在类的对象。因为新类是由已存在类的对象组合而成，所以这种方法称为**组合**(**composition**)。第二种方法要复杂些。我们创建一个新类作为一个已存在类的类型。我们不修改已存在的类，而是采取这个已存在类的形式，并将代码加入其中。这种巧妙的方法称为**继承**(**inheritance**)，其中大量的工作是由编译器完成。

## 14.1 组合语法

实际上，我们一直都在用组合创建类，只不过是在用内部数据类型（有时用string）组合新类。

> 代码示例：
[C14_01_Useful.h](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/14.%20Inheritance%20Composition/C14_01_Useful.h)

```C++
    // C14_01_Useful.cpp
    // A class to reuse
    #ifndef USEFUL_H
    #define USEFUL_H

    class X
    {
        int i;
    public:
        X() {i = 0;}
        void set(int ii) {i = ii;}
        int read() const {return i;}
        int premute() {return i = i * 47;}
    };

    #endif // USEFUL_H

```

在X类中，数值成员是私有的，所以将类型X的一个对象作为公共对象嵌入到一个新类内部，这是绝对安全的。这样就使得新类的接口很简单。

> 代码示例：
[C14_02_Composition.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/14.%20Inheritance%20Composition/C14_02_Composition.cpp)

```C++
    // C14_02_Composition.cpp
    // Resue code with coposition
    #include "C14_01_Useful.h"
    class Y
    {
        int i;
    public:
        X x;    // Embeded object
        Y() { i = 0; }
        void f(int ii) { i = ii; }
        int g() const {return i; } 
    };

    int main()
    {
        Y y;
        y.f(47);
        y.x.set(37);// Access the embeded object
    }
```

访问嵌入对象（称为**子对象**）的成员函数只需再一次的成员选择。

更常见的是把嵌入的对象设为私有，因此它们将成为内部实现的一部分（这意味着如果我们愿意，可以改变这个实现）。新类的公有接口函数包括了对嵌入对象的使用，但没有必要模仿这个对象的接口。

> 代码示例：
[C14_03_Composition2.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/14.%20Inheritance%20Composition/C14_03_Composition2.cpp)

```C++
    // C14_03_Composition2.cpp
    // Private embedded objects
    #include "C14_01_Useful.h"
    class Y
    {
        int i;
        X x;    // Embedded object
    public:
        Y() { i = 0; }
        void f(int ii) { i = ii; x.set(ii);}
        int g() const {return i * x.read();}
        void permute() {x.permute();}
    };

    int main()
    {
        Y y;
        y.f(47);
        y.permute();
    }
```

## 14.2 继承语法

我们规定，在代码中和原来一样给出该类的名字，但在类的左括号的前面，加一个冒号和基类的名字（对于多重继承，要给出多个基类名，它们之间用逗号分开）。当做完这些时，将会自动地得到基类中的所用数据成员和成员函数。

> 代码示例：
[C14_04_Inheritance.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/14.%20Inheritance%20Composition/C14_04_Inheritance.cpp)

```C++
    // C14_04_Inheritance.cpp
    #include "C14_01_Useful.h"
    #include <iostream>
    using namespace std;

    class Y : public X
    {
        int i;  // Different from X's i
    public:
        Y() {i = 0;}
        int change()
        {
            i = permute();  // Different name call
            return i;
        }
        void set(int ii)
        {
            i = ii;
            X::set(ii);
        }
    };

    int main()
    {
        cout << "sizeof(X) = " << sizeof(X) << endl;
        cout << "sizeof(Y) = " << sizeof(Y) << endl;
        Y D;
        D.change();
        // X function interface comes through:
        D.read();
        D.permute();
        // Redefined functions hide base versions:
        D.set(12) ;
    }
```

我们可以看到Y对X进行了继承，这意味着Y将包含X中的所有数据成员和成员函数。实际上，正如没有对X进行继承，而在Y中创建了一个X的成员对象一样，Y是包含了X的一个子对象。无论是成员对象还是基类存储，都被认为是子对象。

本例中的基类前面是public。由于在继承时，基类中所有的成员都是被预设为私有的，所以如果基类的前面没有public，这意味着基类的所有公有成员将在派生类中变为私有的。

在`change()`中，基类的`permute()`函数被调用。即派生类可以直接访问所有基类的公有函数。

当我们重新定义了一个函数的后，仍可能想调用基类的函数。但如果对千`set()`，只是简单地调用`set()`函数，将得到这个函数的本地版本——一个递归的函数调用。为了调用基类的`set()`函数，必须使用作用域运算符来显式地标明基类名。

## 14.3 构造函数的初始化表达式表

对千子对象调用构造函数，C++为此提供了专门的语法，即构造函数的初始化表达式表。在构造函数的初始化表达式表中，可以将对子对象构造函数的调用语句放在构造函数参数表和冒号之后，在函数体的左括号之前。对于从`Bar`继承来的类`MyType`，如果`Bar`的构造函数只有一个`int`型参数，则可以表示为：`MyType::MyType(int i) : Bar(i) {}`。

### 14.3.1 成员对象初始化

显然，对于组合，也可以对成员对象使用同样语法，只是所给出的不是类名；而是对象的名字。如果在初始化表达式表中有多个构造函数的调用，应当用逗号加以隔开：`MyType2::MyType2(int i) : Bar(i), m(i+1){}`。

这是类`MyType2`构造函数的开头，该类是从`Bar`继承来的，并且包含一个称为`m`的成员对象。

### 14.3.2 在初始化表达式表中的内部类型

构造函数的初始化表达式表允许我们显式地调用成员对象的构造函数。事实上，也没有其他方法可以调用那些构造函数。

对于那些没有构造函数的内部类型嵌入对象，为了使语法一致，可以把内部类型看做这样一种类型，它只有一个取单个参数的构造函数，而这个参数于正在初始化的变量的类型相同：

> 代码示例：
[C14_05_PseudoConstructor.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/14.%20Inheritance%20Composition/C14_05_PseudoConstructor.cpp)

```C++
    // C14_05_PseudoConstructor.cpp
    class X
    {
        int i;
        float f;
        char c;
        char* s;
    public:
        X() : i(7), f(1.4), c('x'), s("howdy") {}
    };

    int main()
    {
        X x;
        int i(100);
        int *ip = new int(47);
    }
```

这些“伪构造函数调用”操作可以进行简单的赋值。如果没有显式的进行伪构造函数调用，初始化是不会执行的。

## 14.4 组合和继承的联合

当然，还可以把组合和继承放在一起使用。下面的例子、过继承和组合两种方法创建了一个更复杂的类。

> 代码示例：
[C14_06_Combined.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/14.%20Inheritance%20Composition/C14_06_Combined.cpp)

```C++
    // C14_06_Combined.cpp
    // Inheritance & composition

    class A
    {
        int i;
    public:
        A(int ii) : i(ii) {}
        ~A() {}
        void f() const {}
    };

    class B
    {
        int i;
    public:
        B(int ii) : i(ii) {}
        ~B() {}
        void f() const {}
    };

    class C : public B
    {
        A a;
    public:
        C(int ii) : B(ii), a(ii) {}
        ~C() {}
        void f()  const 
        {
            a.f();
            B::f();
        }
    };

    int main()
    {
        C(47);
    }
```

自动析构函数调用：虽然常常需要在初始化表达式表中做显式构造函数调用，但并不需要做显式的析构函数调用，因为对于任何类型只有一个析构函数，并且它井不取任何参数。然而，编译器仍要保证所有的析构函数被调用，这意味着，在整个层次中的所有析构函数中，从派生最底层的析构函数开始调用，一直到根层。

### 14.4.1 构造函数和析构函数的调用次序

> 代码示例：
[C14_07_Order.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/14.%20Inheritance%20Composition/C14_07_Order.cpp)

```C++

```