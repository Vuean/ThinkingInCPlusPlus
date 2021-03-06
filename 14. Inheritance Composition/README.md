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
    // C14_07_Order.cpp
    // Constructor/destructor order
    #include <fstream>
    using namespace std;
    ofstream out("order.out");

    #define CLASS(ID) class ID {\
    public:\
        ID(int) { out << #ID " constructor\n"; } \
        ~ID() { out << #ID " destructor\n"; } \
    };

    CLASS (Base1);
    CLASS (Member1);
    CLASS (Member2);
    CLASS (Member3);
    CLASS (Member4);

    class Derived1: public Base1
    {
        Member1 m1;
        Member2 m2;
    public:
        Derived1(int) : m2(1), m1(2), Base1(3) 
        {
            out << "Derived1 constructor\n";
        }
        ~Derived1() 
        { 
            out << "Derived1 destructor\n";
        }
    };

    class Derived2: public Derived1
    {
        Member3 m3;
        Member4 m4;
    public:
        Derived2() : m3(1), Derived1(2), m4(3)
        {
            out << "Derived2 constructor\n";
        }
        ~Derived2() 
        { 
            out << "Derived2 destructor\n";
        }
    };

    int main()
    {
        Derived2 d2;
    }
```

程序输出是：

```C++
    Base1 constructor
    Member1 constructor
    Member2 constructor
    Derived1 constructor
    Member3 constructor
    Member4 constructor
    Derived2 constructor
    Derived2 destructor
    Member4 destructor
    Member3 destructor
    Derived1 destructor
    Member2 destructor
    Member1 destructor
    Base1 destructor
```

可以看出，构造是从类层次的最根处开始，而在每一层，首先会调用基类构造函数，然后调用成员对象构造函数。调用析构函数则严格按照构造函数相反的次序。

对于成员对象，构造函数调用的次序完全不受构造函数的初始化表达式表中的次序影响。**该次序是由成员对象在类中声明的次序所决定的**。如果能通过构造函数的初始化表达式表改变构造函数调用次序，那么就会对两个不同的构造函数有两种不同的调用顺序。而析构函数将不能知道如何相应逆序地执行析构，这就产生了相关性问题。

## 14.5 名字隐藏

如果继承一个类并且对它的成员函数重新进行定义，可能会出现两种情况。第一种是正如在基类中所进行的定义一样，在派生类的定义中明确地定义操作和返回类型。这称之为对普通成员函数的**重定义**(**redefining**)，而如果基类的成员函数是虚函数的情况，又可称之为**重写**(**overriding**)。但是如果在派生类中改变了成员函数参数列表和返回类型，会发生什么情况呢：

[C14_08_NameHiding.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/14.%20Inheritance%20Composition/C14_08_NameHiding.cpp)

```C++
    // C14_08_NameHiding.cpp
    // Hiding overloaded names during inheritance
    #include <iostream>
    #include <string>
    using namespace std;

    class Base
    {
    public:
        int f() const
        {
            cout << "B::f() \n";
            return 1;
        }
        int f(string) const {return 1;}
        void g() {}
    };

    class Derived1 : public Base
    {
    public:
        void g() const {}
    };

    class Derived2 : public Base
    {
    public:
        // Redefinition
        int f() const
        {
            cout << "Derived2::f() \n";
            return 2;
        }
    };

    class Derived3 : public Base
    {
    public:
        // Change return type:
        void f() const
        {
            cout << "Derived3::f() \n";
        }
    };

    class Derived4 : public Base
    {
    public:
        // Change argument list:
        int f(int) const
        {
            cout << "Derived4::f() \n";
            return 4;
        }
    };

    int main()
    {
        string s("hello");
        Derived1 d1;
        int x = d1.f();
        d1.f(s);
        Derived2 d2;
        // d2.f(s); // string version hidden
        Derived3 d3;
        // x = d3.f();  // return int version hidden
        Derived4 d4;
        // x = d4.f();  // f() version hidden
        x = d4.f(1);
    }
```

在`Base`类中有一个可被重载的函数`f()`，类`Derived1`并没有对函数`f()`进行任何改变，但它重新定义了函数`g()`。在`main()`中，可以看到函数`f()`的两个重载版本在类`Derived1`中都是可以使用的。但是，由于类`Derived2`重新定义了函数`f()`的一个版本，而对另一个版本没有进行重定义，因此这第二个重载形式是不可以使用的。在类`Derived3`中，通过**改变返回类型**隐藏了基类中的两个函数版本，而在类`Derived4`中，通过**改变参数列表**同样隐藏了基类中的两个函数版本。总体上，可以得出，任何时候重新定义了基类中的一个重载函数，在新类之中所有其他的版本则被自动地隐藏了。在第15章，我们将会看到加上`virtual`这个关键字会对函数的重载有一点影响。

## 14.6 非自动继承的函数

不是所有的函数都能自动地从基类继承到派生类中的。构造函数和析构函数用来处理对象的创建和析构操作，但它们只知道对它们的特定层次上的对象做些什么。所以，在该类以下各个层次中的所有的构造函数和析构函数都必须被调用，也就是说，构造函数和析构函数不能被继承，必须为每一个特定的派生类分别创建。

另外，`operator=`也不能被继承，因为它完成类似于构造函数的活动。下面是由编译器创建的函数的例子：

[C14_09_SynthiesizedFunctions.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/14.%20Inheritance%20Composition/C14_09_SynthiesizedFunctions.cpp)

```C++
    // C14_09_SynthiesizedFunctions.cpp
    // Functions that are synthiesized by the complier

    #include <iostream>
    using namespace std;

    class GameBoard
    {
    public:
        GameBoard()
        {
            cout << "GameBoard() \n";
        }
        GameBoard(const GameBoard&)
        {
            cout << "GameBoard(const GameBoard&) \n";
        }
        GameBoard& operator=(const GameBoard&)
        {
            cout << "GameBoard& operator=(const GameBoard&) \n";
            return *this;
        }
        ~GameBoard()
        {
            cout << "~GameBoard() \n";
        }
    };

    class Game
    {
        GameBoard gb;   // Compisition
    public:
        // Default GameBoard constructor called:
        Game()
        {
            cout << "Game() \n";
        }
        // You must explicitly call the GameBoard
        // copy-constructor or the default constructor
        // is automatically called instead:
        Game(const Game& g) : gb(g.gb)
        {
            cout << "Game(const Game&) \n";
        }
        Game(int)
        {
            cout << "Game(int) \n";
        }
        Game& operator=(const Game& g)
        {
            // You must explicitly call the GameBoard
            // assignment operator or no assignment at
            // all happens for gb:
            gb = g.gb;
            cout << "Game::operator=()\n";
            return *this;
        }
        class Other {};  // Nested class
        // Automatic type conversion:
        operator Other() const
        {
            cout << "Game::operator Other() \n";
            return Other();
        }
        ~Game()
        {
            cout << "~Game() \n";
        }
    };

    class Chess : public Game
    {

    };

    void f(Game::Other) {}

    class Checkers : public Game
    {
    public:
        // Default base-class constructor called:
        Checkers()
        {
            cout << "Checkers() \n";
        }
        // You must explicitly call the base class
        // copy constructor or the default constructor
        // will be automatically called instead:
        Checkers(const Checkers& c) : Game(c)
        {
            cout << "Checkers(const Checkers&) \n";
        }
        Checkers& operator=(const Checkers& c)
        {
            // You must explicitly call the base-class
            // version of opertor=() or no base-class
            // assigment will happen:
            Game::operator=(c);
            cout << "Checkers& operator=() \n";
            return *this;
        }
    };

    int main()
    {
        Chess d1;   // default constructor
        Chess d2(d1);   // copy constructor
        // Chess d3(1);    // Error no int constructor
        d1 = d2;    // operator=() synthiesized
        f(d1);      // Type-conversion is inherited
        Game::Other go;
        // d1 = go;     // Operator= not synthiesized for differing types
        Checkers c1, c2(c1);
        c1 = c2;
    }
```

### 14.6.1 继承和静态成员函数

静态(static) 成员函数与非静态成员函数的共同点：

1)它们均可被继承到派生类中。
2)如果我们重新定义了一个静态成员，所有在基类中的其他重载函数会被隐藏。
3)如果我们改变了基类中一个函数的特征，所有使用该函数名字的基类版本都将会被隐藏。

## 14.7 组合和继承的选择

无论组合还是继承都能把子对象放在新类型中。两者都使用构造函数的初始化表达式表去构造这些子对象。

组合通常是在希望新类内部具有已存在类的功能时使用，而不是希望已存在类作为它的接口。

[C14_10_Car.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/14.%20Inheritance%20Composition/C14_10_Car.cpp)

```C++
    // C14_10_Car.cpp
    // Public composition

    class Engine
    {
    public:
        void start() const {}
        void rev() const {}
        void sttop() const {}
    };

    class Wheel
    {
    public:
        void inflate(int psi) const {}
    };

    class Window
    {
    public:
        void rollup() const {}
        void rolldown() const {}
    };

    class Door
    {
    public:
        Window window;
        void open() const {}
        void close() const {}
    };

    class Car
    {
    public:
        Engine engine;
        Wheel wheel[4];
        Door left, right;
    };

    int main()
    {
        Car car;
        car.left.window.rollup();
        car.wheel[0].inflate(72);
    }
```

### 14.7.1 子类型设置

现在假设想创建`ifstream`对象的一个类，它不仅打开一个文件，而且还保存文件名。这时可以使用组合并把`ifsiream`及`string`都嵌入这个新类中：

[C14_11_FName1.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/14.%20Inheritance%20Composition/C14_11_FName1.cpp)

```C++
    // C14_11_FName1.cpp
    // An fstream with a file name
    #include "../require.h"
    #include <iostream>
    #include <fstream>
    #include <string>
    using namespace std;

    class FName1
    {
        ifstream file;
        string filename;
        bool named;
    public:
        FName1() : named(false) {}
        FName1(const string& fname)
            : filename(fname), file(fname.c_str())
        {
            assure(file, filename);
            named = true;
        } 
        string name() const { return filename;}
        void name(const string& newName)
        {
            if(named) return;
            filename = newName;
            named = true;
        }
        operator ifstream&() {return file;}
    };

    int main()
    {
        FName1 file("FName1.cpp");
        cout << file.name() << endl;
    }
```

但上述仍存在问题：如果希望从ifstream类中的每件东西都拿进来，则需要继承完成子类型化。

### 14.7.2 私有继承

通过在基类表中去掉`public`或者通过显式地声明`private`，可以私有地继承基类。私有继承时，创建的新类具有基类的所有数据和功能，但这些功能是隐藏的，所以它只是部分的内部实现。

通常在想产生像基类接口一样的接口部分，而不允许该对象的处理像一个基类对象时使用私有继承，而不是组合。

#### 14.7.2.1 对私有继承成员公有化

当私有继承时，基类的所有`public`成员都变成了`private`。如果希望它们中的任何一个是可视的，只要用派生类的`public`部分声明它们的名字即可：

[C14_12_PrivateInheritance.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/14.%20Inheritance%20Composition/C14_12_PrivateInheritance.cpp)

```C++
    // C14_12_PrivateInheritance.cpp
    class Pet
    {
    public:
        char eat() const { return 'a'; }
        int speak() const { return 2; }
        float sleep() const { return 3.0; }
        float sleep(int) const { return 4.0; }
    };

    class Goldfish : Pet    // Private inheritance
    {
    public:
        using Pet::eat; // Name publicizes member
        using Pet::sleep; // Both members exposed
    };

    int main()
    {
        Goldfish gf;
        gf.eat();
        gf.sleep();
        gf.sleep(1);
        // gf.speak();  // Error: private member function
    }
```

## 14.8 protected

在实际项目中，有时希望某些东西隐藏起来，但仍允许其派生类的成员访问。于是关键字`protected`派上了用场。它的意思是：“就这个类的用户而言，它是`private`的，但它可被从这个类继承来的任何类使用”。

最好让数据成员是`private`，因为我们应该保留改变内部实现的权利。然后才能通过`protected`成员函数控制对该类的继承者的访问。

[C14_13_Protected.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/14.%20Inheritance%20Composition/C14_13_Protected.cpp)

```C++
    // C14_13_Protected.cpp
    // The protected keyword
    #include <iostream>
    using namespace std;

    class Base
    {
        int i;
    protected:
        int read() const { return i; }
        void set(int ii) { i = ii; }
    public:
        Base(int ii = 0) : i(ii) {}
        int value(int m) const { return m * i;}
    };

    class Derived : public Base
    {
        int j;
    public:
        Derived(int jj = 0) : j(jj) {}
        void change(int x) { set(x); }
        int readd() const {return read();}
    };

    int main()
    {
        Derived d;
        d.change(10);
        cout << d.readd() << endl;
    }
```

### 14.8.1 protected继承

当继承时，基类默认为`private`，这意味着所有`public`成员函数对于新类的用户是`private`的。通常我们都会按`public`进行继承，从而使得基类的接口也是派生类的接口。然而在继承期间，也可以使用`protected`关键字。

保护继承的派生类意味着对其他类来说是“照此实现”，但它是对于派生类和友元是“is-a”。它是不常用的，它的存在只是为了语言的完备性。

## 14.9 运算符的重载和继承

除了赋值运算符以外，其余的运算符可以自动地继承到派生类中。

## 14.10 多重继承

开始时，多重继承看起来似乎很简单：在继承时，只需在基类列表中增加多个类，用逗号隔开。然而，多重继承引起很多含糊的可能性，这就是为什么要在第2卷中专门有一章讨论这个问题的原因。

## 14.11 渐增式开发

继承和组合的优点之一是它支持**渐增式开发**(**incremental development**)，它允许在已存在的代码中引进新代码，而不会给原来的代码带来错误，即使产生了错误，这个错误也只与新代码有关。

## 14.12 向上类型转换

继承的最重要的方面不是它为新类提供了成员函数，而是它是基类与新类之间的关系，这种关系可被描述为“**新类属于原有类的类型**”。

举个例子来说，考虑称为`Instrument`的基类（它表示乐器）和派生类`Wind`（管乐器）。因为继承意味着在基类中的所有函数在派生类中也是可行的，可以发送给基类的消息也可以发送给这个派生类。所以，如果`Instrument`类有`play()`成员函数，那么`Wind`也有。这意味着，可以确切地说，`Wind`对象也就是`Instrument`类型的一个对象。下面的例子表明编译器是如何支持这个概念的：

[C14_14_Instrument.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/14.%20Inheritance%20Composition/C14_14_Instrument.cpp)

```C++
    // C14_14_Instrument.cpp
    // Inheritance & upcasting
    enum note {middleC, Csharp, Cflat};

    class Instrument
    {
    public:
        void play(note) const {}
    };

    // Wind objects are Instruments
    // because they have the same interface:
    class Wind : public Instrument {};

    void tune(Instrument& i)
    {
        // ....
        i.play(middleC);
    }

    int main()
    {
        Wind flute;
        tune(flute);
    }
```

在这个例子中，有趣的是`tune()`函数，它接受一个`Instrument`类型的引用。然而，在`main()`中，在`tune()`函数的调用中却被传递了一个`Wind`参数。

在`tune()`中，这些代码对`Instrument`和从`Instrument`派生来的任何类型都有效，这种将`Wind`的引用或指针转变成`Instrument`引用或指针的活动被称为**向上类型转换**(**upcasting**)。

### 14.12.1 为什么要“向上类型转换”

### 14.12.2 向上类型转换和拷贝构造函数

如果允许编译器为派生类生成拷贝构造函数，它将首先自动地调用基类的拷贝构造函数，然后再是各成员对象的拷贝构造函数（或者在内部类型上执行位拷贝），因此可以得到正确的操作：

[C14_15_CopyConstructor.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/14.%20Inheritance%20Composition/C14_15_CopyConstructor.cpp)

```C++
    // C14_15_CopyConstructor.cpp
    // Correctly creating the copy-constructor
    #include <iostream>
    using namespace std;

    class Parent
    {
        int i;
    public:
        Parent(int i) : i(i)
        {
            cout << "Parent(int ii) \n";
        }
        Parent(const Parent& b) : i(b.i)
        {
            cout << "Parent(const Parent&)\n";
        }
        Parent() : i(0) {cout << "Parent()\n";}
        friend ostream& operator<<(ostream& os, const Parent& b)
        {
            return os << "Parent: " << b.i << endl;
        }
    };

    class Member
    {
        int i;
    public:
        Member(int ii) : i(ii)
        {
            cout << "Member(int ii) \n";
        }
        Member(const Member& m) : i(m.i)
        {
            cout << "Member(const Member&) \n";
        }
        friend ostream& operator<<(ostream& os, const Member& m)
        {
            return os << "Member: " << m.i << endl;
        }
    };

    class Child : public Parent
    {
        int i;
        Member m;
    public:
        Child(int ii) : Parent(ii), i(ii), m(ii)
        {
            cout << "Child(int ii) \n";
        }
        friend ostream& operator<<(ostream& os, const Child& c)
        {
            return os << (Parent&)c << c.m << "Child: " << c.i << endl;
        }
    };

    int main()
    {
        Child c(2);
        cout << "calling copy-constructor: " << endl;
        Child c2 = c;
        cout << "values in c2:\n" << c2;
    }
```

`Child`中的`operator<<`很有意思，它通过将`Child`对象类型转换为`Parent&`，这时编译器把它当做一个`Parent`类型，将调用`operator<<`的`Parent`版本。

我们可以看到`Child`没有显式定义的拷贝构造函数。编译器将通过调用`Parent`和`Member`的拷贝构造函数来生成它的拷贝构造函数。

然而，如果试着为`Child`写自己的拷贝构造函数，并且出现错误：`Child(const Child& c) : i(c.i), m(c.m) {}`。这时将会为`Child`中的基类部分调用默认的构造函数，这是在没有其他的构造函数可供选择调用的情况下，编译器回溯搜索的结果。

此时可能的输出结果是：

```C++
    Parent (int ii)
    Member (int ii)
    Child(int ii)
    calling copy-constructor:
    Parent ()
    Member(const Member&)
    values in c2 :
    Parent: 0
    Member: 2
    Child: 2
```

其中，Parent的值并不是我们所希望的，因为通常我们会希望基类部分从已存在对象拷贝至一个新的对象，以作为拷贝构造函数的一部分。

为了解决这个问题，必须记住无论何时我们在创建了自己的拷贝构造函数时，都要正确地调用基类拷贝构造函数。（此为向上类型转换的另一种情况）：

```C++
    Child(const Child& c)
        ：Parent(c), i(c.i), m(c.m) 
    {
        cout << "Child(Child&) \n";
    }
```

奇怪的部分在于调用`Parent`的拷贝构造函数的地方：`Parent(c)`。因为`Child`是由`Parent`继承而来，所以`Child`的引用也就相当于`Parent`的引用。基类拷贝构造函数的调用将一个`Child`的引用向上类型转换为一个`Parent`的引用，并且使用它来执行拷贝构造函数。当我们创建自己的拷贝构造函数时，也总会做同样的事情。

### 14.12.3 组合与继承

确定应当用组合还是用继承，最清楚的方法之一是**询问是否需要从新类向上类型转换**。

### 14.12.4 指针和引用的向上类型转换

向上类型转换还能出现在对指针或引用简单赋值期间：

```C++
    Wind w;
    Instrument* ip = &w; // Upcast
    Instrument& ir = w; // Upcas
```

### 14.12.5 危机

当然，任何向上类型转换都会损失对象的类型信息。