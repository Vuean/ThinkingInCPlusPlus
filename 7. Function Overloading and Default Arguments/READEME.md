# 7. 第7章 函数重载与默认参数

当我们创建一个对象（一个变量） 时，要为存储区取一个名字。**函数就是一个操作的名字**。函数重载意味着，我们有两个库，它们都有同名的函数，只要它们的**参数列表不同**就不会发生冲突。

C++中有一个很通用的特征叫做**默认参数**(**default argument**)。默认参数就是在用户调用一个函数时没有指定参数值而由编译器插入参数值的参数。

## 7.1 名字修饰

**名字修饰**(**name decoration**)，`void f(); class X {void f();};`。`class X`内的函数`f()`不会于全局的`f()`发生冲突，编译器用不同的内部名`f()`（全局函数）和`X::f()`（成员函数）来区分两个函数。

重载函数的思想是让我们用同名的函数，但这些函数的参数列表应该不一样。编译器会修饰这些名字、范围和参数来产生内部名以供它和连接器使用。

### 7.1.1 用返回值重载

如`void f();`和`int f();`，当编译器能从上下文中惟一确定函数的意思时，如`int x = f();`，这当然没问题。然而，在C中，总是可以调用一个函数但忽略它的返回值，即调用了函数的**副作用**(side effect**)，在这种情况下，编译器如何知道调用哪个函数呢？

### 7.1.2 类型安全连接

**在C++中，所有的函数在被使用前都必须事先声明**。名字修饰会给我们提供一个安全网，这也就是人们常说的**类型安全连接**(**type-safe-linkage**)。

## 7.2 重载的例子

重载的一个很重要的应用是构造函数。

> 代码示例：
[C7_01_Stash3.h]()

```C++
    // C07: Stash3.h
    // Function overloading
    #ifndef STASH3_H
    #define STASH3_H

    class Stash
    {
        int size;           // Size of each space
        int quantity;       // Number of storage spaces
        int next;           // Next empty space
        // Dynamically allocated array of bytes:
        unsigned char* storage;
        void inflate(int increase);
    public:
        Stash(int size);    // Zero quantity
        Stash(int size, int initQuantity); 
        ~Stash();
        int add(void* element);
        void* fetch(int index);
        int count();
    };

    #endif // STASH3_H
```

在第二个构造函数中，有一个Quantity参数指明分配内存位置的初始大小。在这个定义中，可以看到quantity的内部值与storage指针一起被置零。在第二个构造函数中，调用`inflate(initQuantity)`增大quantity的值可以指示被分配的存储空间的大小。

> 代码示例：
[C7_02_Stash3.cpp]()

```C++
    // C07: Stash3.cpp
    #include "C7_01_Stash3.h"
    #include "../require.h"
    #include <iostream>
    #include <cassert>
    using namespace std;
    const int increment = 100;

    Stash::Stash(int sz)
    {
        size = sz;
        quantity = 0;
        next = 0;
        storage = 0;
    }

    Stash::Stash(int sz, int initQuantity)
    {
        size = sz;
        quantity = initQuantity;
        next = 0;
        storage = 0;
        inflate(initQuantity);
    }

    Stash::~Stash()
    {
        if(storage != 0)
        {
            cout << "freeing storage" << endl;
            delete [] storage;
        }
    }

    int Stash::add(void* element)
    {
        if(next >= quantity)    // Enough space left?
            inflate(increment);
        // Copy element into storage
        // starting at the next empty space:
        int startBytes = next * size;
        unsigned char* e = (unsigned char*)element;
        for(int i = 0; i < size; i++)
            storage[startBytes + i] = e[i];
        next++;
        return (next - 1);
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
```

当用第一个构造函数时，没有内存分配给storage，内存是在第一次调用`add()`来增加一个对象时分配的，另外，当执行`add()`时，当前的内存块不够用时也会分配内存。

> 代码示例:
[C7_03_Srash3Test.cpp]()

```C++
    // C07:Stash3Test.cpp
    #include "C7_01_Stash3.h"
    #include "../require.h"
    #include <fstream>
    #include <iostream>
    #include <string>
    using namespace std;

    int main()
    {
        Stash intStash(sizeof(int));
        for(int i = 0; i < 100; i++)
            intStash.add(&i);
        for(int j = 0; j < intStash.count(); j++)
            cout << "intStash.fetch(" << j << ")= "
                << *(int*)intStash.fetch(j) << endl;
        const int bufsize = 80;
        Stash stringStash(sizeof(char) * bufsize, 100);
        ifstream in("C7_03_Stash3Test.cpp");
        assure(in, "C7_03_Stash3Test.cpp");
        string line;
        while (getline(in, line))
            stringStash.add((char*)line.c_str());
        int k = 0;
        char* cp;
        while((cp = (char*)stringStash.fetch(k++)) != 0)
            cout << "stringStash.fetch(" << k << ") = " << cp << endl;
    }
```

## 7.3 联合