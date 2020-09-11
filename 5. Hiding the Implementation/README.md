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
[C5_01_Public.cpp]()

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
[C5_02_Private.cpp]()

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
