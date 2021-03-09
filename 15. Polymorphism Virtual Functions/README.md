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
    // C15_08_AddingVirtuals.cpp
    // Adding Virtual in derivation
    #include <iostream>
    #include <string>
    using namespace std;
    class Pet
    {
        string pname;
    public:
        Pet(const string& petName) : pname(petName) {}
        virtual string name() const { return pname; }
        virtual string speak() const { return "";}
    };

    class Dog : public Pet
    {
        string name;
    public:
        Dog(const string& petName) : Pet(petName) {}
        // New Virtual funciton in the Dog class
        virtual string sit() const 
        {
            return Pet::name() + " sits";
        }
        string speak() const
        {
            return Pet::name() + " says 'Bark!'";
        }
    };

    int main()
    {
        Pet* p[] = {new Pet("generic"), new Dog("Bob")};
        cout << "p[0]->speak() = " << p[0]->speak() << endl;
        cout << "p[1]->speak() = " << p[1]->speak() << endl;
        // cout << "p[1]->sit() = " << p[1]->sit() << endl;
    }
```

类`Pet`中含有2个虚函数：`speak()`和`name()`，而在类`Dog`中又增加了第3个称为`sit()`的虚函数，并且重新定义了`speak()`的含义。

在通常情况下，我们并不知道指针实际上指向哪一种特殊子类的对象，而目前的问题是必须知道所有对象的确切类型，因为我们可能在进行不正确的虚函数调用。然而对于有些情况，如果知道保存在一般容器中的所有对象的确切类型，会使我们的设计工作在最佳状态（或者没有选择）。这就是**运行时类型辨认**(**Run-Time Type
Identification, RTTI**)问题。

RTTI是有关向下类型转换基类指针到派生类指针的问题，向上类型转换是自动发生的，不需强制，因为它是绝对安全的。向下类型转换是不安全的，因为这里没有关于实际类型的编译时信息，所以必须准确地知道这个类实际上是什么类型。如果把它转换成错误的类型，就会出现麻烦。

### 15.8.1 对象切片

当多态地处理对象时，传地址与传值有明显的不同。所有在这里已经看到的例子和将会看到的例子都是传地址的，而不是传值的。这是因为地址都有相同的长度，传递派生类（它通常稍大一些）对象的地址和传递基类（它通常更小一点）对象的地址是相同的。如前面所述，这是使用多态的目的，即让对基类对象操作的代码也能透明地操作派生类对象。

如果对一个对象进行向上类型转换，而不使用地址或引用，发生的事情将会使我们吃惊这个对象被“切片”，直到剩下来的是适合于目的的子对象。

> 代码示例：
[C15_09_ObjectSlicing.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/15.%20Polymorphism%20Virtual%20Functions/C15_09_ObjectSlicing.cpp)

```C++
    // C15_09_ObjectSlicing.cpp
    #include <iostream>
    #include <string>
    using namespace std;

    class Pet
    {
        string pname;
    public:
        Pet(const string& name) : pname(name) {}
        virtual string name() const { return pname; }
        virtual string description() const 
        { 
            return "This is " + pname;
        }
    };

    class Dog : public Pet
    {
        string favoriteActivity;
    public:
        Dog(const string& name, const string& activity)
            : Pet(name), favoriteActivity(activity) {}
        string description() const
        {
            return Pet::name() + " likes to " + favoriteActivity;
        }
    };

    void describe(Pet p)
    {
        cout << p.description() << endl;
    }

    int main()
    {
        Pet p("Alfred");
        Dog d("Fluffy", "sleep");
        describe(p);
        describe(d);
    }
```

在这个程序中，发生了两件事情。第一，`describe()`接受的是一个Pet对象（而不是指针或引用），所以`describe()`中的任何调用都将引起一个与Pet大小相同的对象压栈并在调用后清除。这意味着，如果一个由Pet派生来的类的对象被传给`describe()`，则编译器会接受它，但只拷贝这个对象的对应于Pet的部分，切除这个对象的派生部分。

## 15.9 重载和重新定义

重新定义一个基类中的重载函数将会隐藏所有该函数的其他基类版本。对14章中的NameHiding.cpp进行修改：

> 代码示例：
[C15_10_NameHiding2.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/15.%20Polymorphism%20Virtual%20Functions/C15_10_NameHiding2.cpp)

```C++
    // C15_10_NameHiding2.cpp
    // Virtual functions restrict overloading
    #include <iostream>
    #include <string>
    using namespace std;

    class Base
    {
    public:
        virtual int f() const
        {
            cout << "Base::f()\n";
            return 1;
        }
        virtual void f(string) const {}
        virtual void g() const {}
    };

    class Derived1 : public Base
    {
    public:
        void g() const {}
    };

    class Derived2 : public Base
    {
    public:
        // Overloading a virtual function:
        int f() const
        {
            cout << "Derived2::f()\n";
            return 2;
        }
    };

    class Derived3 : public Base
    {
    public:
        // Cannot change return type
        // void f() const {cout << "Derived3::f()\n";}
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
        x = d2.f();
        // d2.f(s);    // string version hidden

        Derived4 d4;
        x = d4.f(1);
        // x = d4.f(); // f() version hidden
        // d2.f(s);// string version hidden

        Base& br = d4;  // Upcast
        // br.f(1);    // Derived version unavailable
        br.f();     // Base verison available
        br.f(s);
    }
```

首先注意到，在`Derived3`中，编译器**不允许我们改变重新定义过的函数的返回值**（如果`f()`不是虚函数，则是允许的）。这是一个非常重要的限制。

**如果重新定义了基类中的一个重载成员函数，则在派生类中其他的重载函数将会被隐藏。**

### 15.9.1 变量返回类型

上例的类`Derived3`显示了我们不能在重新定义过程中修改虚函数的返回类型。通常是这样的，但也有特例，我们可以稍稍修改返回类型。**如果返回一个指向基类的指针或引用，则该函数的重新定义版本将会从基类返回的内容中返回一个指向派生类的指针或引用**。

> 代码示例：
[C15_11_VariantReturn.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/15.%20Polymorphism%20Virtual%20Functions/C15_11_VariantReturn.cpp)

```C++
    // C15_11_VariantReturn.cpp
    // Returing a pointer or reference to a derived
    // type during ovverriding
    #include <iostream>
    #include <string>
    using namespace std;
    class PetFood
    {
    public:
        virtual string foodType() const = 0;
    };

    class Pet
    {
    public:
        virtual string type() const = 0;
        virtual PetFood* eats() const = 0;
    };

    class Bird : public Pet
    {
    public:
        string type() const {return "Bird";}
        class BirdFood : public PetFood
        {
        public:
            string foodType() const
            {
                return "Bird food";
            }
        };
        // Upcast to base type
        PetFood* eats() {return &bf;}
    private:
        BirdFood bf;
    };

    class Cat : public Pet
    {
    public:
        string type() const {return "Cat";}
        class CatFood : public PetFood
        {
        public:
            string foodType() const {return "Cat food";}
        };
        // Return exact type instead:
        CatFood* eats() {return &cf;}
    private:
        CatFood cf;
    };

    int main()
    {
        Bird b;
        Cat c;
        Pet* p[] = {&b, &c};
        for(int i = 0; i < sizeof p / sizeof *p; i++)
        {
            cout << p[i]->type() << " eats "
                << p[i]->eats()->foodType() << endl;
        }
        // Can return the exact type:
        Cat::CatFood* cf = c.eats();
        Bird::BirdFood* bf;
        // Cannot return the exact type:
        // bf = b.eats();
        // Must downcast:
        bf = dynamic_cast<Bird::BirdFood*>(b.eats());
    }
```

`Bird::eats()`把`BirdFood`向上类型转换到`PetFood`。

## 15.10 虚函数和构造函数

当创建一个包含有虚函数的对象时，必须初始化它的VPTR以指向相应的VTABLE。设置VPTR也是构造函数的工作。如果该类含有虚函数，则生成的构造函数将会包含相应的VPTR初始化代码。

这涉及效率。**内联**(**inline**)函数的作用是对小函数减少调用代价。

### 15.10.1 构造函数调用次序

所有基类构造函数总是在继承类构造函数中被调用。

### 15.10.2 虚函数在构造函数中的行为

对于在构造函数中调用一个虚函数的情况，被调用的只是这个函数的本地版本。也就是说，虚机制在构造函数中不工作。

## 15.11 析构函数和虚拟析构函数

构造函数是不能为虚函数的。但析构函数能够且常常必须是虚的。

构造函数和析构函数是类层次进行调用的惟一地方。

> 代码示例：
[C15_12_VirtualDestructors.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/15.%20Polymorphism%20Virtual%20Functions/C15_12_VirtualDestructors.cpp)

```C++
    // C15_12_VirtualDestructors.cpp
    // Behavior of virtual vs. non-virtual destructor
    #include <iostream>
    using namespace std;
    class Base1
    {
    public:
        ~Base1() {cout << "~Base1()\n";};
    };

    class Derived1 : public Base1
    {
    public:
        ~Derived1() {cout << "~Derived1()\n"; }
    };

    class Base2
    {
    public:
        virtual ~Base2() {cout << "~Base2()\n"; }
    };

    class Derived2 : public Base2
    {
    public:
        ~Derived2() {cout << "~Derived2()\n"; }
    };

    int main()
    {
        Base1 *bp = new Derived1;
        delete bp;
        Base2* b2p = new Derived2;
        delete b2p;
    }
```

输出:

```C++
    ~Base1()
    ~Derived2()
    ~Base2()
```

当运行这个程序时，将会看到`delete bp`只调用基类的析构函数。而当`delete b2p`调用时，在基类的析构函数执行后，派生类析构函数将会执行，这正是我们所希望的。

### 15.11.1 纯虚析构函数

