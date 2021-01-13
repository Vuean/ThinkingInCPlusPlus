# 第11章 引用和拷贝构造函数

在C++中，引用是支持运算符重载语法的基础（见第12章），也为函数参数的传入和传出控制提供了便利。

本章首先简单地介绍一下C和C++的指针的差异，然后介绍引用。但本章的大部分内容将研究对于C++新手来说比较含混的问题：拷贝**构造函数**(**copy-cpnstructor**)。它是一种特殊的构造函数，需要用引用来实现从现有的相同类型的对象中产生新的对象。编译器使用拷贝构造函数通过**按值传递**(**by value**)的方式在函数中传递和返回对象。

本章最后将阐述有点难以理解的C++的**成员指针**(**pointer-to-member**)这个概念。

## 11.1 C++中的指针

C和C++指针的最重要的区别在于C++是一种类型要求更强的语言。C不允许随便地把一个类型的指针赋值给另一个类型，但允许通过`void*`来实现。C++不允许这样做，如果真想把某种类型当做别的类型处理，则必须**显式地**使用类型转换。

## 11.2 C++中的引用

**引用**(**reference**)(`&`)就像能自动地被编译器间接引用的常量型指针。它通常用于函数的参数表中和函数的返回值，但也可以独立使用。例如：

> 代码示例：
[C11_01_FreeStandingReferences.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/11.%20Reference%20and%20the%20Copy-Constructor/C11_01_FreeStandingReferences.cpp)

```C++
    // C11_01_FreeStandingReferences.cpp
    #include<iostream>
    using namespace std;

    // Ordinary free-standing reference:
    int y;
    int& r = y;

    // when a reference is created, it must be initialized to a live object
    // However, you can also say:
    const int& q = 12;  // (1)

    // References are tied to someone eles's storage:
    int x = 0;  // (2)
    int& a = x; // (3)

    int main()
    {
        cout << "x = " << x << ", a = " << a << endl;
        a++;
        cout << "x = " << x << ", a = " << a << endl;
    }
```

在行(1)中，编译器分配了一个存储单元，它的值被初始化为12，于是这个引用就和这个存储单元联系上了。

使用引用时有一定的规则：

1) 当引用被创建时，它必须被初始化（指针则可以在任何时候被初始化）。
2) 一旦一个引用被初始化为指向一个对象，它就不能改变为另一个对象的引用（指针则可以在任何时候指向另一个对象）。
3) 不可能有NULL引用。必须确保引用是和一块合法的存储单元关联。

### 11.2.1 函数中的引用

最经常看见引用的地方是在函数参数和返回值中。当引用被用做函数参数时，在函数内任何对引用的更改将对函数外的参数产生改变。

如果从函数中返回一个引用，必须像从函数中返回一个指针一样对待。当函数返回时，无论引用关连的是什么都应该存在，否则，将不知道指向哪一个内存。

> 代码示例：
[C11_02_Reference.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/11.%20Reference%20and%20the%20Copy-Constructor/C11_02_Reference.cpp)

```C++
    // C11_02_Reference.cpp

    int* f(int* x)
    {
        (*x)++;
        return x;   // safe, x is outside this scope
    }

    int& g(int& x)
    {
        x++;
        return x;   // safe, outside this scope
    }

    int& h()
    {
        int q;
        // return q; // Error
        static int x;
        return x; // Safe, x lives outside this scope
    }

    int main()
    {
        int a = 0;
        f(&a);
        g(a);
    }
```

#### 11.2.1.1 常量引用

在函数参数中使用常屉引用特别重要。这是因为我们的函数也许会接受临时对象，这个临时对象是由另一个函数的返回值创立或由函数使用者显式地创立的。临时对象总是不变的，因此如果不使用常量引用，参数将不会被编译器接受。例如：

> 代码示例：
[C11_03_ConstReferenceArguments.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/11.%20Reference%20and%20the%20Copy-Constructor/C11_03_ConstReferenceArguments.cpp)

```C++
    // C11_03_ConstReferenceArguments.cpp

    // Passing references as const
    void f(int&){}
    void g(const int&) {}
    int main()
    {
        // f(1);   // Error
        g(1);
    }
```

#### 11.2.1.2 指针引用

如果想改变指针本身而不是它所指向的内容，在C++中，可以将函数参数变成指针的引用，不需要取得指针的地址：

> 代码示例：
[C11_04_ReferenceToPointer.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/11.%20Reference%20and%20the%20Copy-Constructor/C11_04_ReferenceToPointer.cpp)

```C++
    // C11_04_ReferenceToPointer.cpp
    #include <iostream>
    using namespace std;
    void increment(int*& i) {i++;}

    int main() 
    {
        int* i = 0;
        cout << "i = " << i  << endl;
        increment(i);
        cout << "i = " << i << endl;
    }
```

### 11.2.2 参数传递准则

传值方式需要调用构造函数和析构函数，然而如果不想改变参数，则可通过常量引用传递，它仅需要将地址压栈。

事实上，只有一种情况不适合用传递地址方式，这就是当传值是惟一安全的途径，否则将会破坏对象时（不想修改外部对象，这不是调用者通常期望的）。

## 11.3 拷贝构造函数

拷贝构造函数，它常被称为`X(X&)`("X引用的X")。在函数调用时，这个构造函数是控制通过传值方式传递和返回用户定义类型的根本所在。

### 11.3.1 按值传递和返回

#### 11.3.1.1 传递和返回大对象

如果创建了一个类，希望通过传值方式传递该类的一个对象，编译器怎样知道做什么？例如：

> 代码示例：
[C11_05_PassingBigStructures.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/11.%20Reference%20and%20the%20Copy-Constructor/C11_05_PassingBigStructures.cpp)

```C++
    // C11_05_PassingBigStructures.cpp
    struct Big
    {
        char buf[100];
        int i;
        long d;
    }B, B2;

    Big bigfun(Big b)
    {
        b.i = 100;
        return b;
    }

    int main()
    {
        B2 = bigfun(B);
    }
```

正如我们猜测的，首先调用函数`bigfun()`，整个B的内容被压栈。

#### 11.3.1.2 函数调用栈框架

