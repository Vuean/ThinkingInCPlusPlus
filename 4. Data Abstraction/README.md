# 4. 数据抽象

库只是他人已经写好的一些代码，按某种方式包装在一起。

## 4.1 一个袖珍C库

一个库通常以一组函数开始，在大多数C库中都有一组struct和一组作用在这些struct之上的函数。如下示例，假设有一个编程工具，当创建时，它的表现像一个数组，但它的长度能在运行时建立。
> 代码示例：
[C4_01_CLib.h]()

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

[C4_01_Clib.cpp]()

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