# 4. 数据抽象

库只是他人已经写好的一些代码，按某种方式包装在一起。

## 4.1 一个袖珍C库

一个库通常以一组函数开始，在大多数C库中都有一组struct和一组作用在这些struct之上的函数。如下示例，假设有一个编程工具，当创建时，它的表现像一个数组，但它的长度能在运行时建立。
> 代码示例：
[C4_01_CLib.h](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/4.%20Data%20Abstraction/C4_01_CLib.h)

```C++
    // C04: C4_01_CLib.h
    // Header file for a C-like library
    // An array-like entity created at runtime

    typedef struct CStatshTag {
        int size;       // size of each space
        int quantity;   // number of storage space
        int next;       // NEXT EMPTY SPACE
        // Dynamically allocated array of bytes:
        unsigned char* storage;
    }CStash;

    void initialize(CStash* s, int size);
    void cleanup(CStash* s);
    int add(CStash* s, const char* element);
    int count(CStash* s);
    void inflate(CStash* s, int increase);
```

[C4_01_Clib.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/4.%20Data%20Abstraction/C4_01_Clib.cpp)

```C++
    // C04: C4_01_Clib.cpp
    // Implementation of example C-like library
    // Declare structure and functions
    #include "C4_01_Clib.h"
    #include <iostream>
    #include <cassert>
    using namespace std;
    // Quantity of elements to add when increasing storage

    const int increment = 100;

    void initialize(CStash* s, int sz)
    {
        s->size = sz;
        s->quantity = 0;
        s->storage = 0;
        s->next = 0;
    }

    int add(CStash* s, const void* element)
    {
        if(s->next >= s->quantity)  // Enough space left?
            inflate(s, increment);
        // Copy element into storage, strating at next empty space:
        int startBytes = s->next * s->size;
        unsigned char* e = (unsigned char*)element;
        for(int i = 0; i < s->size; i++)
            s->storage[startBytes + i] = e[i];
        s->next++;
        return (s->next - 1);   // Index number
    }

    void* fetch(CStash* s, int index)
    {
        // Check index boundaries:
        assert(0 <= index);
        if(index >= s->next)
            return 0;   // To indicate the end
        // Produce pointer to desired element:
        return &(s->storage[index * s->size]);
    }

    int count(CStash *s)
    {
        return s->next; // Elements in CStash
    }

    void inflate(CStash *s, int increase)
    {
        assert(increase > 0);
        int newQuantity = s->quantity + increase;
        int newBytes = newQuantity * s->size;
        int oldBytes = s->quantity * s->size;
        unsigned char* b = new unsigned char[newBytes];
        for(int i = 0; i < oldBytes; i++)
            b[i] = s->storage[i];   // Copy old to new
        delete [](s->storage);  // Old storage
        s->storage = b; // Point to new memory
        s->quantity = newQuantity;
    }

    void cleanup(CStash * s)
    {
        if(s->storage != 0)
        {
            cout << "freeing storage" << endl;
            delete []s->storage;
        }
    }
```

`initialize()`通过设置内部变量为适当的值。完成对`struct CStash`的必要设置。最初，设置·指针为零，表示**不分配初始存储**。

`add()`函数在`CStash`的下一个可用位置上插入一个元素。首先，它检查是否有可用空间，如果没有，它就用后面介绍的`inflate()`函数扩展存储空间。

在`storage`中已经存放有数据字节，由`next`的值指明。为了从正确的字节偏移开始，`next`必须乘上每个元素的长度（按字节），产生`startBytes`，然后，参数`element`转换为一个`unsigned char*`，所以这就能一个字节接着一个字节地寻址，拷贝进可用的`storage`存储空间中。增加后的`next`指向下一个可用的存储块，
`fetch()`能用指向这个数值存放点的“下标数” 重新得到这个值。

`fetch()`首先看`index`是否越界，如果没有越界，返回所希望的变批地址，地址采用`index`参数计算。

### 4.1.1 动态存储分配

事先不知道一个`CStash`需要多大存储空间，所以从堆（heap）中分配由`storage`指向的内存。**堆是很大的内存块，用以在运行时分配一些小的存储空间**。

在标准C中，动态内存分配函数包括`malloc()`、`calloc()`、`realloc()`、`free()`。C++中使用关键字`new`和`delete`。

`new`表达式的一般形式是：`new Type;`。其中`Type`表示希望在堆上分配的变量的类型。**`new`表达式返回指向所请求的准确类型对象的指针**，因此，如果声称`new Type`，返回的是指向`Type`的指针。如果希望`new unsigned char`数组，返回的是**指向这个数的第一个元素的指针**。

`delete`关键字是`new`的对应关键字，任何由`new`分配的内存必须用`delete`释放，否则会造成**内存泄漏（memory leak）**。

释放数组有特殊形式：`delete []myArray;`

堆管理器是相当简单的，它给出一块内存，而当用`delete`释放时又把它收回。

当编译时，如果在**栈**上创建一个变量，那么这个变量的存储单元由编译器自动开辟和释放。编译器准确地知道需要多少存储容量，根据这个变量的活动范围知道这个变量的生命期。

而对动态内存分配，编译器不知道需要多少存储单元，不知道它们的生命期，不能自动清除。

为了测试这个库，我们创建两个CStash。第一个存放int，第二个存放由80个char组成
的数组：
> 代码示例：
[C4_02_CLibTest.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/4.%20Data%20Abstraction/C4_02_CLibTest.cpp)

```C++
    // C04: C4_02_CLibTest.cpp
    // Test the C-like library
    #include "C4_01_CLib.h"
    #include <iostream>
    #include <fstream>
    #include <string>
    #include <cassert>
    using namespace std;

    int main()
    {
        // Define variables at the beginning of the block, as in C:
        CStash intStash, stringStash;
        int i;
        char *cp;
        ifstream in;
        string line;
        const int bufsize = 80;
        // Now remember to initialize the variables:
        initialize(&intStash, sizeof(int));
        for(int i = 0; i < 100; i++)
        {
            add(&intStash, &i);
        }
        for (i = 0; i < count(&intStash); i++)
        {
            cout << "fetch(&intStash, " << i << ") = "
                << *(int*)fetch(&intStash, i)
                << endl;
        }
        initialize(&stringStash, sizeof(char)*bufsize);
        in.open("CLibTest.cpp");
        assert(in);
        while (getline(in, line))
            add(&stringStash, line.c_str());
        i = 0;
        while ((cp = (char*)fetch(&stringStash, i++)) != 0)
            cout << "fetch(&stringStash, " << i << ") = "
                << cp << endl;
        cleanup(&intStash);
        cleanup(&stringStash);
    }
```

C++有严格的类型检查， 它不允许直接向其他类型赋`void*`(C允许)。

## 4.2 哪儿出问题

在C中，使用库的最大的障碍之一是**名字冲突(name clashes)**。

## 4.3 基本对象

C++中，函数可以放在`struct`内部，作为“成员函数”。`CStash`的C版本翻译成C++的`Stash`后是：
> 代码示例：
[C4_03_CPPLib.h](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/4.%20Data%20Abstraction/C4_03_CPPLib.h)

```C++
// C04: C4_03_CPPLib.h
struct Statsh{
    int size;       // size of each space
    int quantity;   // number of storage space
    int next;       // NEXT EMPTY SPACE
    // Dynamically allocated array of bytes:
    unsigned char* storage;

    void initialize(int size);
    void cleanup();
    int add(const char* element);
    int count();
    void inflate(int increase);
};
```

在C+＋中，不是硬性传递这个结构的地址作为在这个结构上运算的所有函数的第一个参数，而是编译器秘密地做这件事。

`::` 作用域解析运算符。
> 代码示例:
[C4_03_CPPLib.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/4.%20Data%20Abstraction/C4_03_CPPLib.cpp)

```C++
// C04: C4_03_CPPLib.cpp
// Declare structure and functions:
#include "C4_03_CPPLib.h"
#include <iostream>
#include <cassert>
using namespace std;

// Quantity of elements to add when increasing Storage:
const int increment= 100;

void Stash::initialize(int sz)
{
    size = sz;
    quantity = 0;
    storage = 0;
    next = 0;
}

int Stash::add(const void* element)
{
    if(next >= quantity)
        inflate(increment);
    int startBytes = next * size;
    unsigned char* e = (unsigned char*)element;
    for (int i = 0; i < size; i++)
    storage[startBytes + i] = e[i];
    next++;
    return (next - 1);
}

void* Stash::fetch(int index)
{
    assert(0 <= index);
    if (index >= next)
        return 0;
    return &(storage[index * size]);
}

int Stash::count()
{
    return next;
}

void Stash::inflate(int increase)
{
    assert(increase > 0);
    int newQuantity = quantity + increase;
    int newBytes = newQuantity * size;
    int oldBytes = quantity * size;
    unsigned char* b = new unsigned char[newBytes];
    for (int i = 0; i < oldBytes; i++)
        b[i] = storage[i];
    delete []storage;
    storage = b;
    quantity = newQuantity;
}

void Stash::cleanup()
{
    if (storage != 0)
    {
        cout << "freeing storage" << endl;
        delete []storage;
    }
}
```

头文件中的声明是由编译器要求的。在C++中，不能调用未事先声明的函数，否则编译器将报告一个出错信息。

在C中，可以赋`void*`给任何指针，但C++中，这是不允许的，因为类型在C++中是严格的。

```C++
    int i = 10;
    void* vp = &i;  // OK in both C and C++
    int* ip = vp;   // Only acceptable in C;
```

C++允许将任何类型的指针赋给`void*`（这是`void*`的最初的意图，它需要足够大，以存放任何类型的指针），但不允许将`void`指针赋给任何其他类型的指针。

在下面的测试程序中，可以看到`Stash`的C++版本所使用的另一些东西。
> 代码示例:
[C4_03_CPPLibTest.cpp]()

```C++
    #include "C4_03_CPPLib.h"
    #include "../require.h"
    #include <fstream>
    #include <iostream>
    #include <string>
    using namespace std;

    int main() {
        Stash intStash;
        intStash.initialize(sizeof(int));
        for (int i = 0; i < 100; i++)
            intStash.add(&i);
        for (int j = 0; j < intStash.count(); j++)
            cout << "intStash.fetch(" << j << ") = "
                << *(int*)intStash.fetch(j)
                << endl;
        // Ñòðîêè èç 80 ñèìâîëîâ:

        Stash stringStash;
        const int bufsize = 200;
        stringStash.initialize(sizeof(char) * bufsize);

        ifstream in("CppLibTest.cpp");
        assure(in, "CppLibTest.cpp");
        string line;
        while (getline(in, line))
            stringStash.add(line.c_str());

        int k = 0;
        char* cp;
        while ((cp = (char*)stringStash.fetch(k++)) != 0)
            cout << "stringStash.fetch" << k << ") = "
                << cp << endl;
        intStash.cleanup();
        stringStash.cleanup();
    }
```

## 4.4 什么是对象

将函数放在结构体内，结构体就变成了新的创造物，它技能描写属性，又能描写行为，这就形成了**对象**的概念。

在C++中，**对象就是变量**，它的最纯正的定义是“一块存储区”（更准确地可称为：对象必须有惟一的标识）。

## 4.5 抽象数据类型

将数据连同函数捆绑在一起的能力可以用千创建新的数据类型。这常常被称为**封装(encapsulation)**。

## 4.6 对象细节

一个`struct`的大小是它的所有成员大小的和。有时，当一个`struct`被编译器处理时，会增加额外的字节以使得边界整齐，这主要是为了提高执行效率。

用`sizeof()`运算符确定`struct`的长度：

> 代码示例:
[C4_04_Sizeof.cpp]()

```C++
    // C04: C4_04_Sizeof.cpp
    // sizeof struct
    #include <iostream>
    #include "C4_01_Clib.h"
    #include "C4_03_CPPLib.h"
    using namespace std;

    struct A{
        char c;
        int i[100]; // 单独一个数组时是400字节
    };

    struct B{
        void f();
    };

    void B::f() {}

    int main()
    {
        cout << "sizeof struct A = " << sizeof(A) << " bytes." << endl;
        cout << "sizeof struct B = " << sizeof(B) << " bytes." << endl;
        cout << "sizeof CStash in C = " << sizeof(CStash) << " bytes." << endl;
        cout << "sizeof CStash in C++ = " << sizeof(Stash) << " bytes." << endl;
        return 0;
    }
```

`struct B`在C中是不允许的，在C++中，以这种选择方式创建一个`struct`，惟一的目的就是划定函数名的范围，所以这是允许的。**对象的基本规则之一是每个对象必须有一个惟一的地址，因此，无数据成员的结构总应当有最小的非零长度**。

## 4.7 头文件形式

通常在头文件中方放入**声明**信息，头文件告诉编译器在我们的库中哪些是可用的。**头文件是存放接口规范的地方**。

### 4.7.1 头文件的重要性

在C++中，如果在一个头文件中声明了一个`struct`，我们在使用`struct`的任何地方和定义这个`struct`成员函数的任何地方必须包含这个头文件。如果不经声明就调用常规函数，调用或定义成员函数，C++编译器会给出错误消息。通过强制正确地使用头文件，语言保证库中的一致性，并通过在各处强制使用相同的接口，可以减少程序错误。

### 4.7.2 多次声明的问题

头文件的第二个问题是：如果把一个`struct`声明放在一个头文件中，就有可能在一个编译程序中多次包含这个头文件，可能存在**多次包含和重声明**的危险。

C和C++都**允许重声明函数**，只要两个声明匹配即可，但是两者都**不允许重声明结构**。

### 4.7.3 预处理器指示#define、#ifdef、#endif

预处理器指示`#define`可以用来创建编译时标记。可以选择预处理器被定义，但不指定特定的值：`#define FLAG`；或给它一个值：`#define PI 3.14159`。

无论哪种情况，预处理器都能测试该标记，检查它是否已经被定义：`#ifdef FLAG`，这将得到一个真值，`#ifdef`后面的代码将包含在发送给编译器的包中。当预处理器遇到语句`#endif`或`#endif //FLAG`时包含终止。

`#define`的反意是`#undef`，它将使得使用相同变量的`#ifdef`语句得到假值。`#undef`还引起预处理器停止使用宏。`#ifdef`的反意是`#ifndef`，如果标记还没有定义，它得到真值。