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
[C4_02_CLibTest.cpp]()

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
[C4_03_CPPLib.h]()

```C++

```