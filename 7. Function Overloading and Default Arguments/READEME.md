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
[C7_01_Stash3.h](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/7.%20Function%20Overloading%20and%20Default%20Arguments/C7_01_Stash3.h)

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
[C7_02_Stash3.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/7.%20Function%20Overloading%20and%20Default%20Arguments/C7_02_Stash3.cpp)

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
[C7_03_Srash3Test.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/7.%20Function%20Overloading%20and%20Default%20Arguments/C7_03_Stash3Test.cpp)

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

struct和class惟一的不同之处就在于，struct默认为public，而class默认为private。

一个**union**（**联合**）也可以带有构造函数、析构函数、成员函数甚至访问控制。

> 代码示例:
[C7_04_UnionClass.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/7.%20Function%20Overloading%20and%20Default%20Arguments/C7_04_UnionClass.cpp)

```C++
    // C07:UnionClass.cpp
    // Union with constructors and member functions
    #include <iostream>
    using namespace std;

    union U
    {
    private:
        int i;
        float f;
    public:
        U(int a);
        U(float b);
        ~U();
        int read_int();
        float read_float();
    };

    U::U(int a) {i = a;}

    U::U(float b) {f = b;}

    U::~U() {cout << "U::~U()\n";}

    int U::read_int() {return i;}

    float U::read_float() {return f;}

    int main()
    {
        U X(12), Y(1.9F);
        cout << X.read_int() << endl;
        cout << Y.read_float() << endl;
    }
```

`union`与`class`的**惟一不同之处在于存储数据的方式**（也就是说**在
`union`中int类型的数据和float类型的数据在同一内存区覆盖存放**），但是`union`不能在继承时作为基类使用。

尽管成员函数使客户程序员对`union`的访问在一定程度上变得规范，但是，一旦`union`被初始化，仍然不能阻止他们选择错误的元素类型。例如在上面的程序中，即使不恰当，我们也可以写`X.read_float()`，然而，一个更安全的`union`可以封装在一个类中。在下面的例子中，
注意`enum`是如何阐明代码的。以及重载是如何同构造函数一起出现的。

> 代码示例:
[C7_05_SuperVar.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/7.%20Function%20Overloading%20and%20Default%20Arguments/C7_05_SuperVar.cpp)

```C++
    // C07:SuperVar.cpp
    // A Super-variable
    #include <iostream>
    using namespace std;

    class SuperVar
    {
        enum{
            character,
            integer,
            floating_point
        } vartype;  // Define one
        union { // another union
            char c;
            int i;
            float f;
        };

    public:
        SuperVar(char ch);
        SuperVar(int ii);
        SuperVar(float ff);
        void print();
    };

    SuperVar::SuperVar(char ch)
    {
        vartype = character;
        c = ch;
    }

    SuperVar::SuperVar(int ii)
    {
        vartype = integer;
        i = ii;
    }

    SuperVar::SuperVar(float ff)
    {
        vartype = floating_point;
        f = ff;
    }

    void SuperVar::print()
    {
        switch(vartype)
        {
            case character:
                cout << "character: " << c << endl;
                break;
            case integer:
                cout << "integer: " << i << endl;
                break;
            case floating_point:
                cout << "float: " << f << endl;
                break;
        }
    }

    int main()
    {
        SuperVar A('c'), B(12), C(1.44F);
        A.print();
        B.print();
        C.print();
    }
```

在上面的代码中，`enum`没有类型名（它是一个没有加标记的枚举），如果想立即定义`enum`的一个实例时，上面的这种做法是可取的。

`union`没有类型名和标识符。这叫做**匿名联合**(**anonymous union**)，为这个`union`创建空间，但并不需要用标识符的方式和以点操作符('.')方式访问这个`union`的元素。例如，如果匿名`union`是：

> 代码示例:
[C7_06_AnonymousUnion.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/7.%20Function%20Overloading%20and%20Default%20Arguments/C7_06_AnonymousUnion.cpp)

```C++
    // C07:AnonymousUnion.cpp
    int main()
    {
        union{
            int i;
            float f;
        };
        // Acess members without using quantities
        i = 12;
        f = 1.22;
    }
```

注意：**我们访问一个匿名联合的成员就像访问普通的变量一样。惟一的区别在于：该联合的两个变量占用同一内存空间**。**如果匿名`union`在文件作用域内（在所有函数和类之外），则它必须被声明为`static`, 以使它有内部的连接。**

## 7.4 默认参数

默认参数是在函数声明时就已给定的一个值，如果在调用函数时没有指定这一参数的值，编译器就会自动地插上这个值。

