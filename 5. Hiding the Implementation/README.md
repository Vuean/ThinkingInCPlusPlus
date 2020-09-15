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
[C5_03_Friend.cpp]()

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