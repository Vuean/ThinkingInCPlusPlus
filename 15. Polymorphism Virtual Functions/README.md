# 第15章 多态性和虚函数

**多态性**(**polymorphism**)提供了接口与具体实现之间的另一层隔离，从而将"what"与"how"分离开来。多态性改善了代码的组织性和可读性，同时也使创建的程序具有可扩展性，程序不仅在项目的最初创建期可以“扩展”，而且当在项目需要有新的功能时也能“扩展”。

**封装**(**encapsulation**)通过组合特性和行为来生成新的数据类型。访问控制通过使细节数据设为`private`，将接口从具体实现中分离开来。

## 15.1 C++程序员的演变

## 15.2 向上类型转换

取一个对象的地址（指针或引用），并将其作为基类的地址来处理，这被称为**向上类型转换**(**upcasting**)，因为继承树的绘制方式是以基类为顶点的。

但也存在一些问题：

> 代码示例：
[C15_01_Instrument2.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/15.%20Polymorphism%20Virtual%20Functions/C15_01_Instrument2.cpp)

```C++
    // C15_01_Instrument2.cpp
    // Inheritance & upcasting
    #include <iostream>
    using namespace std;
    enum note {middleC, Csharp, Cflat};

    class Instrument
    {
    public:
        void play(note) const 
        {
            cout << "Instrument::play" << endl;
        }
    };

    // Wind objects are Instruments
    // because they have the same interface:
    class Wind : public Instrument 
    {
    public:
        // Redefine interface function:
        void play(note) const
        {
            cout << "Wind::play" << endl;
        }
    };

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

函数`tune()`（通过引用）接受一个`Instrument`，但也不拒绝任何从`Instrument`派生的类。在`main()`中，可以看到，无需类型转换，就能将`Wind`对象传给`tune()`。这是可接受的；在`Instrument`中的接口必然存在于`Wind`中，因为`Wind`是从`Instrument`中按公有方式继承而来的。`Wind`到`Instrument`的**向上类型转换**会使`Wind`的接口“变窄”，但不会窄过`Instrument`的整个接口。

处理指针时采用相同的参数；**惟一的不同是用户必须显式地取对象的地址传给函数**。

## 15.3 问题

运行程序`Instrument2.cpp`可以看到这个程序中的问题。调用输出的是`Instrument::play`。显然，这不是所希望的输出，因为我们知道这个对象实际上是Wind而不是一个`Instrument`。应当调用的是`Wind::play`。为此，由`Instrument`派生的任何对象不论它处于什么位置都应当使用它的`play()`版本。

然而，当对函数用C方法肘，`Instrument2.cpp`的行为并不使人惊奇。为了理解这个问题，需要知道**捆绑**(**binding**）的概念。

### 15.3.1 函数调用捆绑

**把函数体与函数调用相联系称为捆绑**(**binding**)。上面程序中的问题是早捆绑引起的，因为编译器在只有`Instrmnent`地址时它并不知道要调用的正确函数。

解决方法被称为**晚捆绑**(**late binding**)，这意味着捆绑根据对象的类型，发生在运行时。晚捆绑又称为**动态捆绑**(**dynamic binding**)或**运行时捆绑**(**runtime binding**)。

## 15.4 虚函数

对于特定的函数，为了引起晚捆绑，C++要求在基类中声明这个函数时使用`virtual`关键字。**晚捆绑只对virtual函数起作用**，而且只在使用含有`virtual`函数的基类的地址时发生。

为了创建一个像`virtual`这样的成员函数，仅需要在函数声明时使用关键字`virtual`。如果一个函数在基类中被声明为`virtual`，那么在所有的派生类中它都是`virtual`的。在派生类中`virtual`函数的重定义通常称为**重写**(**overriding**)。

> 代码示例：
[C15_02_Instrument3.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/15.%20Polymorphism%20Virtual%20Functions/C15_02_Instrument3.cpp)

```C++
    // C15_02_Instrument3.cpp
    // Late bidding with the virtual keyword
    #include <iostream>
    using namespace std;
    enum note {middleC, Csharp, Cflat};

    class Instrument
    {
    public:
        virtual void play(note) const 
        {
            cout << "Instrument::play" << endl;
        }
    };

    // Wind objects are Instruments
    // because they have the same interface:
    class Wind : public Instrument 
    {
    public:
        // Redefine interface function:
        void play(note) const
        {
            cout << "Wind::play" << endl;
        }
    };

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

这个文件除了增加了`virtual`关键字之外，一切与`Instrument2.cpp`相同，但结果明显不一样。现在输出调用的是`Wind::play`。

### 15.4.1 扩展性

**可扩展的**(**extensible**)，是指可以通过从公共基类继承新数据类型而增加新功能。操作基类接口的函数完全不需要改变就可以适合于这些新类。

> 代码示例：
[C15_03_Instrument4.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/15.%20Polymorphism%20Virtual%20Functions/C15_03_Instrument4.cpp)

```C++
    // C15_03_Instrument4.cpp
    #include <iostream>
    using namespace std;
    enum note {middleC, Csharp, Cflat};

    class Instrument
    {
    public:
        virtual void play(note) const 
        {
            cout << "Instrument::play" << endl;
        }
        virtual char* what() const
        {
            return "Instrument";
        }
        virtual void adjust(int){}
    };

    // Wind objects are Instruments
    // because they have the same interface:
    class Wind : public Instrument 
    {
    public:
        // Redefine interface function:
        void play(note) const
        {
            cout << "Wind::play" << endl;
        }
        char* what() const { return "Wind"; }
        void adjust(int) {}
    };

    class Percussion : public Instrument
    {
    public:
        void play(note) const
        {
            cout << "Percussion::play" << endl;
        }
        char* what() const { return "Percussion"; }
        void adjust(int) {}
    };

    class Stringed : public Instrument
    {
    public:
        void play(note) const
        {
            cout << "Stringed::play" << endl;
        }
        char* what() const { return "Stringed"; }
        void adjust(int) {}
    };

    class Brass : public Wind
    {
    public:
        void play(note) const
        {
            cout << "Brass::play" << endl;
        }
        char* what() const { return "Brass"; }
    };

    class Woodwind : public Wind
    {
    public:
        void play(note) const
        {
            cout << "Woodwind::play" << endl;
        }
        char* what() const { return "Woodwind"; }
    };

    void tune(Instrument& i)
    {
        // ....
        i.play(middleC);
    }

    void f(Instrument& i)
    {
        i.adjust(1);
    }

    Instrument* A[] = {
        new Wind,
        new Percussion,
        new Stringed,
        new Brass,
    };

    int main()
    {
        Wind flute;
        Percussion drum;
        Stringed violin;
        Brass flugelhorn;
        Woodwind recorder;
        tune(flute);
        tune(drum);
        tune(violin);
        tune(flugelhorn);
        tune(recorder);
        f(flugelhorn);
    }
```

## 15.5 C++如何实现晚捆绑

利用虚函数，即使在编译器还不知道这个对象的特定类型的情况下，也能调用这个对象中正确的函数。

### 15.5.1 存放类型信息

在任何类中不存在显式的类型信息，因为类型信息被隐藏了。为了看到这些信息，这里举一个例子，以便检查使用虚函数的类的长度，并
与没有虚函数的类进行比较。

> 代码示例：
[C15_04_Sizes.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/15.%20Polymorphism%20Virtual%20Functions/C15_04_Sizes.cpp)

```C++
    // C15_04_Sizes.cpp
    // Object sizes with/without virtual functions
    #include <iostream>
    using namespace std;

    class NoVirtual
    {
        int a;
    public:
        void x() const {}
        int i() const { return 1;}
    };

    class OneVirtual
    {
        int a;
    public:
        virtual void x() const {}
        int i() const { return 1;}
    };

    class TwoVirtual
    {
        int a;
    public:
        virtual void x() const {}
        virtual int i() const { return 1;}
    };

    int main()
    {
        cout << "int: " << sizeof(int) << endl;
        cout << "NoVirtual: " << sizeof(NoVirtual) << endl;
        cout << "void* : " << sizeof(void*) << endl;
        cout << "OneVirtual: " << sizeof(OneVirtual) << endl;
        cout << "TwoVirtual: " << sizeof(TwoVirtual) << endl;
    }
```

不带虚函数，对象的长度恰好就是所期望的长度：单个int的长度。而带有单个虚函数的`OneVirtual`，对象的长度是`NoVirtual`的长度加上一个`void`指针的长度。它反映出，如果有一个或多个虚函数，编译器都只在这个结构中插入一个单个指针(VPTR)。因此`OneVirtual`和`TwoVirtuals`的长度没有区别。这是因为VPTR指向一个存放函数地址的表。我们只需要一个表，因为所有虚函数地址都包含在这个单个表中。

### 15.5.2 虚函数功能图示

### 15.5.3 撩开面纱

### 15.5.4 安装vpointer

### 15.5.5 对象是不同的

如果编译器有一个它知道确切类型的对象，那么（在C++中）对任何函数的调用将不再使用晚捆绑，或至少编译器不必使用晚捆绑。因为编译器知道对象的确切类型，为了提高效率，当调用这些对象的虚函数时，很多编译器使用早捆绑。

> 代码示例：
[C15_05_Early.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/15.%20Polymorphism%20Virtual%20Functions/C15_05_Early.cpp)

```C++
    // C15_05_Early.cpp
    // Early biding & virtual functions
    #include <iostream>
    #include <string>
    using namespace std;

    class Pet
    {
    public:
        virtual string speak() const { return ""; }
    };

    class Dog : public Pet
    {
    public:
        string speak() const { return "Bark!"; }
    };

    int main()
    {
        Dog ra1ph;
        Pet* p1 = &ra1ph;
        Pet& p2 = ra1ph;
        Pet p3;
        // Late biding for both
        cout << "p1->speak() = " << p1->speak() << endl;
        cout << "p2->speak() = " << p2.speak() << endl;
        // Early biding(probably)
        cout << "p3->speak() = " << p3.speak() << endl;
    }
```

在`p1->speak()`和`p2.speak()`中，使用地址，就意味着信息不完全：p1和p2可能表示`Pet`的地址，也可能表示其派生对象的地址，所以必须使用虚函数。而当调用`p3.speak()`时不存在含糊，编译器知道确切的类型且知道它是一个对象，所以它不可能是由`Pet`派生的对象，而确切的只是一个`Pet`。这样，可以使用早捆绑。

## 15.6 为什么需要虚函数

virtual关键字可以改变程序的效率。

## 15.7 抽象基类和纯虚函数

在设计时，常常希望基类仅仅作为其派生类的一个接口。可以在
基类中加入至少一个**纯虚函数**(**pure virtual function**)，来使基类成为**抽象(abstract)类**。纯虚函数使用关键字virtual，并且在其后面加上=0。如果某人试着生成一个抽象类的对象，编译器会制止他。

当继承一个抽象类时，**必须实现所有的纯虚函数**，否则继承出的类也将是一个抽象类。创建一个纯虚函数允许在接口中放置成员函数，而不一定要提供一段可能对这个函数毫无意义的代码。同时，**纯虚函数要求继承出的类对它提供一个定义**。

建立公共接口的惟一原因是它能对千每个不同的子类有不同的表示。它建立一个基本的格式。

> 代码示例：
[C15_06_Instrument5.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/15.%20Polymorphism%20Virtual%20Functions/C15_06_Instrument5.cpp)

```C++
    // C15_06_Instrument5.cpp
    // Pure abstract base classes
    #include <iostream>
    using namespace std;
    enum note {middleC, Csharp, Cflat};

    class Instrument
    {
    public:
        virtual void play(note) const = 0;
        virtual char* what() const = 0;
        virtual void adjust(int) = 0;
    };

    // Wind objects are Instruments
    // because they have the same interface:
    class Wind : public Instrument 
    {
    public:
        // Redefine interface function:
        void play(note) const
        {
            cout << "Wind::play" << endl;
        }
        char* what() const { return "Wind"; }
        void adjust(int) {}
    };

    class Percussion : public Instrument
    {
    public:
        void play(note) const
        {
            cout << "Percussion::play" << endl;
        }
        char* what() const { return "Percussion"; }
        void adjust(int) {}
    };

    class Stringed : public Instrument
    {
    public:
        void play(note) const
        {
            cout << "Stringed::play" << endl;
        }
        char* what() const { return "Stringed"; }
        void adjust(int) {}
    };

    class Brass : public Wind
    {
    public:
        void play(note) const
        {
            cout << "Brass::play" << endl;
        }
        char* what() const { return "Brass"; }
    };

    class Woodwind : public Wind
    {
    public:
        void play(note) const
        {
            cout << "Woodwind::play" << endl;
        }
        char* what() const { return "Woodwind"; }
    };

    void tune(Instrument& i)
    {
        // ....
        i.play(middleC);
    }

    void f(Instrument& i)
    {
        i.adjust(1);
    }


    int main()
    {
        Wind flute;
        Percussion drum;
        Stringed violin;
        Brass flugelhorn;
        Woodwind recorder;
        tune(flute);
        tune(drum);
        tune(violin);
        tune(flugelhorn);
        tune(recorder);
        f(flugelhorn);
    }
```

注意，**纯虚函数禁止对抽象类的函数以传值方式调用**。这也是防止**对象切片**(object slicing)（这将会被简单地介绍）的一种方法。通过抽象类，可以保证在向上类型转换期间总互是使用指针或引用。

### 15.7.1 纯虚定义

在基类中，对纯虚函数提供定义是可能的。我们仍然告诉编译器不允许产生抽象基类的对象，而且如果要创建对象，则纯虚函数必须在派生类中定义。

正如下面的纯虚定义：

> 代码示例：
[C15_07_PureVirtualDefinitions.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/15.%20Polymorphism%20Virtual%20Functions/C15_07_PureVirtualDefinitions.cpp)

```C++
    // C15_07_PureVirtualDefinitions.cpp
    // Pure virtual base definitions
    #include <iostream>
    using namespace std;

    class Pet
    {
    public:
        virtual void speak() const = 0;
        virtual void eat() const = 0;
        // Inline pure virtual definitions illegal:
        // virtual void sleep() const = 0;
    };

    // OK, not defined inline
    void Pet::eat() const
    {
        cout << "Pet::eat()" << endl;
    }

    void Pet::speak() const
    {
        cout << "Pet::speak()" << endl;
    }

    class Dog : public Pet
    {
    public:
        // use the common Pet code:
        void speak() const { Pet::speak();}
        void eat() const { Pet::eat();}
    };

    int main()
    {
        Dog simba;
        simba.speak();
        simba.eat();
    }
```

这个特点的另一个好处是，它允许我们实现从常规虚函数到纯虚函数的改变，而无需打乱已存在的代码。

### 15.8 继承和VTABLE

对于可被创建的每个对象（即它的类不含有纯虚函数），在VTABLE中总有一个函数地址的全集，所以绝对不能对不在其中的地址进行调用。

但是在**派生**(**derived**)类中继承或增加新的虚函数时会发生什么呢？

> 代码示例：
[C15_08_AddingVirtuals.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/15.%20Polymorphism%20Virtual%20Functions/C15_08_AddingVirtuals.cpp)

```C++

```