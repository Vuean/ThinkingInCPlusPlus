# 6. 初始化与清除

安全性包括初始化和清除两个方面。在C++中，初始化和清除的概念是简化库的使用的关键所在，并可以减少那些在客户程序员忘记去完成这些操作时会引起的细微错误。

## 6.1 用构造函数确保初始化

类的设计者可以通过提供一个叫做**构造函数**(**constructor**)的特殊函数来保证每个对象都被初始化。

构造函数的名字与类的名字一样。这样的函数在初始化时会自动被调用。传递到构造函数的第一个（秘密）参数是this指针，也就是调用这一函数的对象的地址，不过，对构造函数来说，this指针指向一个没有被初始化的内存块，构造函数的作用就是正确的初始化该内存块。

## 6.2 用析构函数确保清除

析构函数的语法与构造函数一样，用类的名字作为函数名。然而析构函数前面加上一个代字号（~），以和构造函数区别。另外，析构函数不带任何参数，因为析构不需任何选项。

> 代码示例:
[C6_01_Constructor.cpp]()

```C++
    // C6_01_Constructor.cpp
    // Constructors & destructors
    #include <iostream>
    using namespace std;

    class Tree
    {
        int height;
    public:
        Tree(int initialHeight);    // Constructor
        ~Tree(); // Destructor
        void grow(int years);
        void printsize();
    };

    Tree::Tree(int initialHeight)
    {
        height = initialHeight;
    }

    Tree::~Tree()
    {
        cout << "inside Tree destructors" << endl;
        printsize();
    }

    void Tree::grow(int years){
        height += years;
    }

    void Tree::printsize()
    {
        cout << "Tree heights is " << height << endl;
    }

    int main()
    {
        cout << "before opening brace: " << endl;
        {
            Tree t(12);
            cout << "after Tree creation" << endl;
            t.printsize();
            t.grow(4);
            cout << "before closing brace: " << endl;
        }
        cout << "after closing brace: " << endl;
    }

    /*
        运行结果：
        before opening brace:
        after Tree creation
        Tree heights is 12
        before closing brace:
        inside Tree destructors
        Tree heights is 16
        after closing brace:
    */
```

可以看到析构函数在包括它的右括号处被调用。

## 6.3 清除定义块

在C++中，对一个对象适用的所有规则，对内部类型的对象也同样适用。这意味着任何类的对象或者内部类型的变量都可以在块的任何地方定义。这也意味着可以等到已经知道一个变量的必要信息时再去定义它，所以总是可以同时定义和初始化一个变量。

> 代码示例:
[C6_02_DefineInitialize.cpp]()

```C++
    // C06: DefineInitialize.cpp
    // Defining variables anywhere
    # include "..\require.h"
    # include <iostream>
    #include <string>
    using namespace std;

    class G
    {
        int i;
    public:
        G(int ii);
    };

    G::G(int ii) { i = ii; }

    int main()
    {
        cout << "initialization value? ";
        int retval = 0;
        cin >> retval;
        require(retval != 0);
        int y = retval + 3;
        G g(y);
    }
```

上例中可以看到先是执行一些代码，然后retval被定义和初始化，接着是一条用来接受客户程序员输入的语句，最后定义y和g。然而，在C中这些变量都只能在块的开始处定义。

一般说来，应该在尽可能靠近变址的使用点处定义变量，并在定义时就初始化，以减少变量在块中的生命周期，减少该变量在块的其他地方被误用的机会。

### 6.3.1 for循环

```C++
    for(int j = 0; j < 100; j++)
        cout << "j = " << j << endl;
    for(int i = 0; i < 100; i++)
        cout << "i = " << i << endl;
```

变量i和j都是在for表达式中直接定义的（在C中不能这样做），然后它们就可以作为一个变量在for循环中使用。

要注意局部变量会屏蔽其封闭块内的其他同名变量。通常，使用与全局变量同名的局部变量会使人产生误解， 并且也易于产生错误。

### 6.3.2 内存分配

一个变量可以在某个程序范围内的任何地方定义，所以在这个变量的定义之前是无法对它分配内存空间的。即使存储空间在块的一开始就被分，构造函数也仍然要到对象的定义时才会被调用，因为标识符只有到此时才有效。

> 代码示例
[C6_03_Nojump.cpp]()

```C++
    // C06: Nojump.cpp
    // Can't jump past constructors

    class X
    {
    public:
        X();
    };

    X::X() {}

    void f(int i)
    {
        if (i < 10)
        {
            // !goto jumpl; // error: goto bypass init
        }
        X x1;   // Constructor called here
        jumpl:
        switch (i)
        {
            case 1: 
                X x2;
                break;
            case 2:
                X x3;
                break;
        }
    }

    int main()
    {
        f(9);
        f(11);
    }
```

这里讨论的内存分配都是在堆栈中进行的。内存分配是通过编译器向下移动堆栈指针来实现的（这里的“向下”是相对而言的，实际指针值增加，还是减少，取决于机器）。也可以在堆栈中使用new为对象分配内存。

## 6.4 带有构造函数和析构函数的Stash

建立带有构造函数和析构函数的Stash头文件。

> 代码示例：
[C6_04_Stash2.h]()

```C++
    // C06: Stash2.h
    // With Constructors and Destructors
    #ifndef STASH2_H
    #define STASH2_H

    class Stash
    {
        int size;           // Size of each space
        int quantity;       // Number of storage spaces
        int next;           // Next empty space
        // Dynamically allocated array of bytes:
        unsigned char* storage;
        void inflate(int increase);     // inflate：使充气，使膨胀
    public:
        Stash(int size);
        ~Stash();
        int add(void* element);
        void* fetch(int index);         // fetch：取，拿
        int count();
    };

    #endif // STASH2_H
```

以下为实现文件，用构造函数和析构函数分别代替了initialize()和cleanup()函数。

> 代码示例：
[C6_05_Stash2.cpp]()

```C++
    // C06:Stash2.cpp
    // Constructors & destructors
    #include "C6_04_Stash2.h"
    #include "../require.h"
    #include <iostream>
    #include <cassert>
    using namespace std;
    const int increment = 100;

    Stash::Stash(int sz)
    {
        size = sz;
        quantity = 0;
        storage = 0;
        next = 0;
    }

    int Stash::add(void* element)
    {
        if(next >= quantity)    // Enough space left?
            inflate(increment);
        // Copy element into storage
        // starting at next empty space:
        int startBytes = next * size;
        unsigned char* e = (unsigned char*) element;
        for (int i = 0; i < size; i++)
            storage[startBytes + i] = e[i];
        next++;
        return (next - 1);  // Index number
    }

    void* Stash::fetch(int index)
    {
        require(0 <= index, "Stash::fetch (-)index");
        if(index >= next)
            return 0;   // To indicate the end
        // Produce pointer to desired element:
        return &(storage[index * size]);
    }

    int Stash::count()
    {
        return next;    // Number of elements in CStash
    }

    void Stash::inflate(int increase)
    {
        require(increase > 0, "Stash::inflate zero or negative increase");
        int newQuantity = quantity + increase;
        int newBytes = newQuantity * size;
        int oldBytes = quantity * size;
        unsigned char* b = new unsigned char[newBytes];
        for(int i = 0; i < oldBytes; i++)
            b[i] = storage[i];  // Copy old to new
        delete [] (storage);    // Delete old storage
        storage = b;    // point to new memory
        quantity = newQuantity;
    }

    Stash::~Stash()
    {
        if(storage != 0)
        {
            cout << "freeing storage" << endl;
            delete [] storage;
        }
    }
```

`require.h`中的函数是用来监视程序员错误的， 代替函数`assert()`的作用。但是函数`assert()`对失败操作的输出不及`require.h`的函数有效。

因为`inflate()`是私有的，所以`require()`不能正确执行的惟一情况就是：其他成员函数意外地把一些不正确的值传递给了`inflate()`。


嵌套的结构并不能自动获得访问`private`成员的权限。要获得访问私有成员的权限，必须遵守特定的规则：**首先声明（而不定义）一个嵌套的结构，然后声明它是全局范围使用的一个`friend`，最后定义这个结构**。结构的定义必须与`friend`声明分开，否则编译器将不把它看做成员。

> 代码示例：
[C5_04_NestFriend.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/5.%20Hiding%20the%20Implementation/C5_04_NestFriend.cpp)

```C++
    // C05: C5_04_NestFriend.cpp
    // Nested friends
    #include <iostream>
    #include <cstring>  // memset()
    using namespace std;
    const int sz = 20;

    struct Holder{
    private:
        int a[sz];
    public:
        void initialize();
        struct Pointer;
        friend Pointer;

        struct Pointer{
        private:
            Holder* h;
            int* p;
        public:
            void initialize(Holder* h);
            // Move around in the array
            void next();
            void previous();
            void top();
            void end();
            // Access values:
            int read();
            void set(int i);
        };
    };

    void Holder::initialize()
    {
        memset(a, 0, sz * sizeof(int));
    }

    void Holder::Pointer::initialize(Holder* rv)
    {
        h = rv;
        p = rv->a;
    }

    void Holder::Pointer::next()
    {
        if(p < &(h->a[sz - 1])) p++;
    }

    void Holder::Pointer::previous()
    {
        if(p > &(h->a[0])) p--;
    }

    void Holder::Pointer::top()
    {
        p = &(h->a[0]);
    }

    void Holder::Pointer::end()
    {
        p = &(h->a[sz - 1]);
    }

    int Holder::Pointer::read()
    {
        return *p;
    }

    void Holder::Pointer::set(int i)
    {
        *p = i;
    }

    int main()
    {
        Holder h;
        Holder::Pointer hp, hp2;
        int i;

        h.initialize();
        hp.initialize(&h);
        hp2.initialize(&h);

        for(int i = 0; i < sz; i++)
        {
            hp.set(i);
            hp.next();
        }

        hp.top();
        hp2.end();

        for(i = 0; i < sz; i++)
        {
            cout << "hp = " << hp.read() << ", hp2 = " << hp2.read() << endl;
            hp.next();
            hp2.previous();
        }
    }
```

一旦`Pointer`被声明，它就可以通过`friend Pointer;`语句来获得访问Holder的私有成员的权限。

`struct Holder`包含一个`int`数组和一个`Pointer`，可以通过`Pointer`来访问这些整数。因为`Pointer`与`Holder`紧密联系，所以有必要将它作为结构`Holder`中的一个成员。但是，又因为`Pointer`是同`Holder`分开的，所以程序员可以在函数`main()`中定义它们的多个实例，然后用它们来选择数组的不同部分。

使用标准C语言库函数`memset()`（在`<cstring>`中）可以使上面的程序变得容易。它把起始于某一特定地址的内存（该内存作为第一个参数）从起始地址直至其后的n（n作为第三个参数）个字节的所有内存都设置成同一个特定的值（该值作为第二个参数）。

## 5.4 对象布局

在一个特定的“访问块”（被访问说明符限定的一组声明）内，这些变量在内存中是连续存放的。

## 5.5 类

访问控制通常是指实现**细节的隐藏(implementation hiding)**。将函数包含到一个结构内(常称为封装)来产生一种带数据和操作的数据类型，由访问控制在该数据类型之内确定边界。原因有：第一，可以决定哪些客户程序员可以用， 哪些客户程序员不能用；第二，可将具体实现与接口分离开来。

C++中class和struct在每个方面都是一样的，**除了class中的成员默认为`private`，而struct中的成员默认为`public`**。

> 代码示例：
[C5_05_Class.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/5.%20Hiding%20the%20Implementation/C5_05_Class.cpp)

```C++
    // C05: C5_05_Class.cpp
    // Similarity of struct and class

    struct A
    {
    private:
        int i, j, k;
    public:
        int f();
        void g();
    };

    int A::f()
    {
        return i + j + k;
    }

    void A::g()
    {
        i = j = k = 0;
    }

    // Identical results are produced with:

    class B
    {
        int i, j, k;
    public:
        int f();
        void g();
    };

    int B::f()
    {
        return i + j + k;
    }

    void B::g()
    {
        i = j = k = 0;
    }

    int main()
    {
        A a;
        B b;
        a.f(); a.g();
        b.f(); b.g();
    }
```

### 5.5.1 用访问控制来修改Stash

现在把第4章的例子用类及访问控制来改写一下。请注意客户程序员的接口部分现在已经很清楚地区分开了，完全不用担心客户程序员会偶然地访问到他们不该访问的内容了。

> 代码示例：
[C5_06_Stash.h](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/5.%20Hiding%20the%20Implementation/C5_06_Stash.h)

```C++
    // C05:C5_06_Stash.h
    // Converted to use access control
    #ifndef C5_06_STASH_H
    #define C5_06_STASH_H
    class Stash
    {
        int size;       // size of each space
        int quantity;   // number of storage spaces
        int next;       // next empty space
        // Dynamically allocated array of bytes:
        unsigned char* storage;
        void inflate (int increase);
    public:
        void initialize(int size);
        void cleanup();
        int add(void* element);
        void* fetch(int index);
        int count();
    };

    #endif // C5_06_STASH_H
```

`inflate()`函数声明为`private`，因为它只被`add()`函数调用，所以它属于内部实现部分，不属于接口部分。

### 5.5.2 用访问控制来修改Stack

对于第二个例子，我们把`Stack`改写成一个类。现在嵌套的数据结构是`private`。这样做的好处是可以确保客户程序员既看不到，也不依赖于`Stack`的内部表示：
> 代码示例：
[C5_07_Stack2.h](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/5.%20Hiding%20the%20Implementation/C5_07_Stack2.h)

```C++
    // C05: C5_07_Stack2.h
    // Nested structs via linked list

    #ifndef C5_07_STACK2_H
    #define C5_07_STACK2_H

    class Stack {
        struct Link{
            void* data;
            Link* next;
            void initialize(void* dat, Link* nxt);
        }* head;
    public:
        void initialize();
        void push(void* dat);
        void* peek();
        void* pop();
        void cleanup();
    };
    #endif // C5_07_STACK2_H
```

## 5.6 句柄类

C++中的访问控制允许将实现部分与接口部分分开，但实现部分的隐藏是不完全的。包含私有实现部分会带来两个影响：一是即使客户程序员不能轻易地访问私有实现部分，但可以看到它；二是造成一些不必要的重复编译。

### 5.6.1 隐藏实现

为保证项目得安全性，就有必要把一个编译好的实际结构放在实现文件中，而不是让其暴露在头文件中。

### 5.6.2 减少重复编译

在我们的编程环境中，当一个文件被修改，或它所依赖的头文件被修改时，项目管理员需要重复编译该文件。这就是通常所说的**易碎的基类问题(fragile base-class problem)**。如果这个项目非常大，用于编译的时间过多可能妨碍项目的快速转型。

解决这个问题的技术有时称为**句柄类( handle class)**或称为“Cheshire cat”。有关实现的任何东西都消失了，只剩一个单指针"smile"。该指针指向一个结构，该结构的定义与其所有的成员函数的定义一同出现在实现文件中。这样，只要接口部分不改变，头文件就不需变动。而实现部分可以按需要任意更改，完成后只需要对实现文件进行重新编译，然后重新连接到项目中。

头文件中只包含公共的接口和一个单指针，该单指针指向一个没有完全定义的类。

> 代码示例：
[C5_08_Handle.h](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/5.%20Hiding%20the%20Implementation/C5_08_Handle.h)

```C++
    // C05: C5_08_Handle.h
    // Handle classes
    #ifndef C5_08_HANDLE_H
    #define C5_08_HANDLE_H
    class Handle
    {
        struct Cheshire;    // class declaration only
        Cheshire* smile;
    public:
        void initialize();
        void cleanup();
        int read();
        void change(int);
    };

    #endif // C5_08_HANDLE_H
```

这是所有客户程序员都能看到的。下面这行`struct Cheshire;`是一个**不完全的类型说明(incomplete type specification)**或**类声明(class declaration)**[类
定义(class definition)包含类的主体]。它告诉编译器，`Cheshire`是一个结构名，但没有提供有关该`struct`的任何细节。这些信息对产生一个指向`struct`的指针来说已经足够了。但在提供了一个结构的主体部分之前不能创建一个对象。在这种技术里，包含具体实现的结构体被隐藏在实现文件中。

> 代码示例：
[C5_08_Handle.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/5.%20Hiding%20the%20Implementation/C5_08_Handle.cpp)

```C++
    // C5: C5_08_Handle.cpp
    // Handle implementation
    #include "C5_08_Handle.h"

    // Define Handle's implementation:
    struct Handle::Cheshire
    {
        int i;
    };

    void Handle::initialize()
    {
        smile = new Cheshire;
        smile->i = 0;
    }

    void Handle::cleanup()
    {
        delete smile;
    }

    int Handle::read()
    {
        return smile->i;
    }

    void Handle::change(int x)
    {
        smile->i = x;
    }
```

`Cheshire`是一个嵌套结构，所以它必须用作用域符定义：`Struct Handle::Ches hire`。在`Handle::initialize()`中，为`Cheshire`结构分配存储空间，在`Haiidle::cleanup()`中，释放这些存储空间。这些内存被用来代替类的所有`private`部分。当编译`Handle.cpp`时，这个结构的定义被隐藏在目标文件中，没有人能看到它。如果改变了`Cheshire`的组成，惟一要重新编译的是`Handle.cpp`，因为头文件并没有改动。

`Handle`的使用就像任何类的使用一样，包含头文件、创建对象、发送消息。

> 代码示例：
[C5_08_UseHandle.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/5.%20Hiding%20the%20Implementation/C5_08_UseHandle.cpp)

```C++
// C05: C5_08_UseHandle.cpp
// USe the Handle class
#include "C5_08_Handle.h"

int main()
{
    Handle h;
    h.initialize();
    h.read();
    h.change(1);
    h.cleanup();
}
```

## 5.7 小结

**第一: private,public,protected的访问范围:**

private: 只能由该类中的函数、其友元函数访问，不能被其他任何访问，该类的对象也不能访问；

protected: 可以被该类中的函数，子类的函数，以及其友元函数访问，不能被该类的对象访问；

public: 可以被该类中的函数，子类中的函数，其友元函数访问，也可以由该类的对象访问。

**第二：类继承后方法属性变化：**

使用private继承，父类的所有方法在子类中变为private；

使用protected继承，父类的protected和public方法在子类中变为protected, private方法不变；

使用public继承，父类的方法属性不发生改变。

**三种访问权限：**

public:可以被任意实体访问

protected:只允许子类及本类的成员函数访问

private:只允许本类的成员函数访问

**三种继承方式：**

public 继承

protect 继承

private 继承

**组合结果：**

基类中 继承方式 子类中

public ＆ public继承 => public

public ＆ protected继承 => protected

public ＆ private继承 = > private

protected ＆ public继承 => protected

protected ＆ protected继承 => protected

protected ＆ private继承 = > private

private ＆ public继承 => 子类无权访问

private ＆ protected继承 => 子类无权访问

private ＆ private继承 = > 子类无权访问

由以上组合结果可以看出

1、public继承不改变基类成员的访问权限

2、private继承使得基类所有成员在子类中的访问权限变为private

3、protected继承将基类中public成员变为子类的protected成员，其它成员的访问 权限不变。

4、基类中的private成员不受继承方式的影响，子类永远无权访问。

此外，在使用private继承时，还存在另外一种机制：准许访问 。

我们已经知道，在基类以private方式被继承时，其public和protected成员在子类中变为private成员。然而某些情况下，需要在子类中将一个或多个继承的成员恢复其在基类中的访问权限。

C++支持以两种方式实现该目的

方法一，使用using 语句，这是C++标准建议使用的方式

方法二，使用访问声明，形式为 base-class::member;， 位置在子类中适当的访问声明处。(注，只能恢复原有访问权限，而不能提高或降低访问权限)
