# 5. 隐藏实现

本章重点讨论结构中得边界问题。

## 5.1 设置限制

在任何关系中，设立相关各方都遵从的边界是很重要的。一且建立了一个库，我们就与该库的**客户程序员(client programmer)**建立了一种关系，客户程序员需要用我们的库来编写应用程序或建立另外的库。

需要控制对结构成员的访问有两个理由：一是让客户程序员远离一些他们不需要使用的工具，这些工具对数据类型内部的处理来说是必需的，但对客户程序员解决特定问题的接口
却不是必须的。

访问控制的理由之二是允许库的设计者改变struct的内部实现，而不必担心会对客户程序员产生影响。

## 5.2 C++的访问控制

C++中的**访问说明符(access specifier)**包括：`public`、`private`、`protected`。无论什么时候使用访问说明符， 后面必须加一个冒号。

`public`意味着在其后声明的所有成员可以被所有的人访问。`public`成员就如同一般的`struct`成员。比如，下面的`struct`声明是相同的：

> 代码示例:
[C5_01_Public.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/5.%20Hiding%20the%20Implementation/C5_01_Public.cpp)

```C++
    // C05: C5_01_Public.cpp
    // Public is just like C's struct

    struct A
    {
        int i;
        char c;
        float f;
        void func();
    };
    void A::func() {}

    struct B
    {
    public:
        int i;
        char c;
        float f;
        void func();
    };
    void B::func() {}

    int main()
    {
        A a; B b;
        a.i = b.i = 1;
        a.c = b.c = 'c';
        a.f = b.f = 1.0;
        a.func();
        b.func();
    }
```

`priVate`关键字则意味着，除了该类型的创建者和类的内部成员函数之外，任何人都不能访问。在上面的例子中，我们可以让`struct B`中的部分数据成员隐藏起来，只有我们自己能访问它们：

> 代码示例:
[C5_02_Private.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/5.%20Hiding%20the%20Implementation/C5_02_Private.cpp)

```C++
// C05: C5_02_Private.cpp
// Setting the boundary

struct B
{
private:
    char c;
    float f;
public:
    int i;
    void func();
};

void B::func()
{
    i = 0;
    c = 'a';
    f = 1.0;
}

int main()
{
    B b;
    b.i = 1;    // OK, public
    // b.c = 'c';  // Error, private
    // b.f = 3.14;
}
```

虽然`func()`函数可以访问B的所有成员，但一般的全局函数如`main()`函数却不能访问。当然其他结构的成员函数同样也不能访问。只有那些在结构声明(“合约”）中明确声明的函数才能访问这些`private`成员。

`protected`和`private`基本相似，只有一点不同，继承的结构可以访问`protected`成员，但不能访问`private`成员。

## 5.3 友元

在某结构内部声明一个函数为**friend（友元）**，则该不属于当前结构的函数可以当前结构中的数据。**一个`friend`必须在一个结构内声明**。

程序员可以把一个全局函数声明为`friend`，也可以把另一个结构中的成员函数甚至整个结构都声明为`friend`。

> 代码示例：
[C5_03_Friend.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/5.%20Hiding%20the%20Implementation/C5_03_Friend.cpp)

```C++
    // C05: C5_03_Friend.cpp
    // Friend allows special access

    // Declaration (incomplete type specification):
    # include <iostream>
    using namespace std;
    struct X;

    struct Y{
        void f(X*);
    };

    struct X{
    private:
        int i;
    public:
        void initialize();
        friend void g(X*, int); // Global friend
        friend void Y::f(X*);   // struct member friend
        friend struct Z;        // Entire struct os a friend
        friend void h();
    };

    void X::initialize()
    {
        i = 0;
    }

    void g(X* x, int i)
    {
        x->i = i;
    }

    void Y::f(X* x)
    {
        x->i = 47;
    }

    struct Z{
    private:
        int j;
    public:
        void initialize();
        void g(X* x);
    };

    void Z::initialize()
    {
        j = 99;
    }

    void Z::g(X* x)
    {
        x->i += j;
        cout << x->i;
    }

    void h()
    {
        X x;
        x.i = 100;  // Direct data manipulation
    }

    int main()
    {
        X x;
        x.initialize();
        Z z;
        z.initialize();
        z.g(&x);
    }
```

此例中，`struct Y`有一个成员函数`f()`，它将修改`X`类型的对象。但因为C++的编译器要求在引用任一变最之前必须先声明，所以`struct Y`必须在它的成员`Y::f(X*)`被声明为`struct X`的一个友元之前声明，但要声明`Y::f(X*)`，又必须先声明`struct X`。

因为`Y::f(X*)`引用了一个`X`对象的**地址(address)**，所以即使编译器还没有完全知道这种对象类型大小，也知道如何传递地址。但如果试图传递整个对象，编译器就必须知道`X`的全部定义以确定它的大小以及如何传递，这就使得**程序员无法去声明一个类似于`y::g(X)`的函数**。

通过传递`X`的地址，编译器允许程序员在声明`Y::f(X*)`之前做一个`X`的**不完全的类型说明(incomplete type specification)**--`struct X`。

该声明仅仅是告诉编译器，有一个叫`X`的`struct`，所以当它被引用时，只要不涉及名字以外的其他信息，就不会产生错误。

其他两个friend函数，第一个声明将一个全局函数`g()`作为一个`friend`，但`g()`在
这之前并没有在全局范围内作过声明，**这表明`friend`可以在声明函数的同时又将它作为`struct`的友元**。

这种扩展声明对整个结构体同样有效：`friend struct Z;`，是`Z`的一个不完全的类型说明，并把整个结构都当做一个`friend`。

### 5.3.1 嵌套友元

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
[C5_06_Stash.h]()

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
[C5_07_Stack2.h]()

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