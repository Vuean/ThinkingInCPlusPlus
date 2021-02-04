# 第13章 动态对象创建

C早就提供了**动态内存分配**(**dynamic memory allocation**)函数`malloc()`和`free()`（以及`malloc()`的变体），这些函数在运行时从**堆（也称自由内存）**中分配存储单元。

在C++中这些函数将不能很好地运行。因为构造函数不允许我们向它传递内存地址来进行初始化。如果那么做了，我们可能：

1. 忘记了。则在C++中有保证的对象初始化将会难以保证；
2. 期望发生正确的事，但在对对象进行初始化之前意外地对对象进行了某种操作；
3. 把错误规模的对象传递给它。

在堆上创建对象时确保构造函数调用是特别重要的。使动态对象创建成为语言的核心。`malloc()`和`free()`是库函数，因此不在编译器控制范围之内。

在本章中，我们将明白C++的`new`和`delete`是如何通过在堆上安全地创建对象来出色地解决这个问题。

## 13.1 对象创建

当创建一个C++对象时，会发生两件事：

l) 为对象分配内存。
2) 调用构造函数来初始化那个内存。

C+＋强迫这样做是因为未初始化的对象是程序出错的主要原因。对象在哪里如何被创建无关紧要，但构造函数一定需要被调用。

然而，步骤1)可以用几种方式或在可选择的时间发生：

1) 在静态存储区域，存储空间在程序开始之前就可以分配；这个存储空间在程序的整个运行期间都存在。
2) 无论何时到达一个特殊的执行点（左大括号）时，存储单元都可以在栈上被创建。出了执行点（右大括号），这个存储单元自动被释放。这些栈分配运算内置千处理器的指令集中。
3) 存储单元也可以从堆（也被称为自由存储单元）的地方分配。这被称为动态内存分配。在运行时调用程序分配这些内存。这意味着可以在任何时候决定分配内存及分配多少内存。当然也需负责决定何时释放内存。

这三个区域经常被放在一块连续的物理存储单元里：静态内存、栈和堆，没有确定的规则。

### 13.1.1 C从堆中获取存储单元的方法

为了在运行时动态分配内存，C在它的标准库函数中提供了一些函数：从堆中申请内存的函数`malloc()`以及它的变种`calloc()`和`realloc()`、释放内存返回给堆的函数`free()`。为了使用C的动态内存分配函数在堆上创建一个类的实例，我们必须这样做：

> 代码示例：
[C13_01_MallocClass.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/13.%20Dynamic%20Object%20Creation/C13_01_MallocClass.cpp)

```C++
    // C13_01_MallocClass.cpp
    // Malloc with class objects
    // What you'd have to do if not for "new"
    #include "../require.h"
    #include <cstdlib>  // malloc() & free()
    #include <cstring>
    #include <iostream>
    using namespace std;

    class Obj
    {
        int i, j, k;
        enum {sz = 100};
        char buf[sz];
    public:
        void initialize()
        {
            // can't use constructor
            cout << "Initializing Obj" << endl;
            i = j = k = 0;
            memset(buf, 0, sz);
        }
        void destory() const
        {
            // can't use destructor
            cout << "Destoring Obj" << endl;
        }
    };

    int main()
    {
        Obj* obj = (Obj*)malloc(sizeof(Obj));
        require(obj != 0);
        obj->initialize();
        // ... sometime later
        obj->destory();
        free(obj);
    }
```

`malloc()`为对象分配内存，但用户必须决定对象得长度，而且`malloc()`只分配了一块内存，而不是生成一个对象，所以返回的是一个`void*`类型指针。而C++不允许将一个`void*`类型指针赋予任何其他指针，所以必须做类型转换。

因为`malloc()`可能找不到可分配的内存(在这种情况下它返回0)，所以必须检查返回的指针以确保内存分配成功。

最容易出问题的是`obj->initialize();`，用户在使用对象前必须对它初始化。，而且构造函数不能被显示调用，是在对象创建时由编译器调用。

### 13.1.2 opearator new

C++中的解决方案是把创建一个对象所需的所有动作都结合在一个称为`new`的运算符里。当用`new`(`new`的表达式)创建一个对象时，它就在堆里为对象分配内存并为这块内存调用构造函数：`MyType *fp = new MyType();`

默认的`new`还进行检查以确信在传递地址给构造函数之前内存分配是成功的，所以不必显式地确定调用是否成功。

### 13.1.3 operator delete

`new`表达式的反面是`delete`表达式。`delete`表达式首先调用析构函数，然后释放内存。`delete`只用于删除由`new`创建的对象，为了避免一个对象删除两次而带来的问题，通常建议再删除指针后理级将指针赋值为0（空指针）。

### 13.1.4 一个简单的例子

> 代码示例：
[C13_02_Tree.h](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/13.%20Dynamic%20Object%20Creation/C13_02_Tree.h)

```C++
    // C13_02_Tree.h
    #ifndef TREE_H
    #define TREE_H
    #include <iostream>

    class Tree
    {
        int height;
    public:
        Tree(int treeHeight) : height(treeHeight) {}
        ~Tree() {std::cout << "~Tree() delete t";}
        friend std::ostream& operator<<(std::ostream& os, const Tree* t)
        {
            return os << "Tree height is: " << t->height << std::endl;
        }
    };
    #endif // TREE_H
```

> 代码示例：
[C13_02_Tree.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/13.%20Dynamic%20Object%20Creation/C13_02_Tree.cpp)

```C++
    // C13_02_Tree.cpp
    // Simple demo of new & delete
    #include "C13_02_Tree.h"
    using namespace std;

    int main()
    {
        Tree* t = new Tree(40);
        cout << t;
        delete t;
    }
```

### 13.1.5 内存管理的开销

当在堆栈里自动创建对象时，对象的大小和它们的生存期被准确地内置在生成的代码里，这是因为编译器知道确切的类型、数量和范围。而**在堆里创建对象还包括另外的时间和空间的开销**。

## 13.2 重新设计前面的例子

使用`new`和`delete`，对于本书前面介绍的`Stash`例子。

### 13.2.1 使用delete void*可能出错

如果想对一个`void*`类型指针进行`delete`操作，要注意这将可能成为一个程序错误，除非指针所指的内容是非常简单的，因为，它将不执行析构函数。下面的例子将显示发生的情况：

> 代码示例：
[C13_03_BadVoidPointerDeletion.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/13.%20Dynamic%20Object%20Creation/C13_03_BadVoidPointerDeletion.cpp)

```C++
// C13_03_BadVoidPointerDeletion.cpp
// Deleting void pointers can cause memory leaks
    #include <iostream>
    using namespace std;

    class Object
    {
        void* data; // some storage
        const int size;
        const char id;
    public:
        Object(int sz, char c) : size(sz), id(c)
        {
            data = new char[size];
            cout << "constructing object" << id 
                << ", size = " << size << endl;
        }
        ~Object()
        {
            cout << "Destructing object" << id << endl;
            delete []data;  // OK just release storage
            // no destructor calls are necessary
        }
    };

    int main()
    {
        Object* a = new Object(40, 'a');
        delete a;
        void* b = new Object(40, 'b');
        delete b;
    }
```

类`Object`包含了一个`void*`指针，它被初始化指向“元”数据（它没有指向含有析构函数的对象）。在`Object`的析构函数中，对这个`void*`指针调用`delete`并不会发生什么错误，因为所需要的仅是释放这块内存。

因为`delete a`知道`a`指向一个`Object`对象，所以析构函数将会被调用，从而释放了分配给`data`的内存。但是，正如在进行`delete b`的操作中，如果通过`void*`类型的指针对一个对象进行操作，则只会释放`Object`对象的内存，而不会调用析构函数，也就不会释放`data`所指向的内存。

### 13.2.2 对指针的清除责任

解决内存泄漏的另一个工作在于确保对容器中的每一个对象调用`delete`。如果把指向在栈上创建的对象的指针和指向在堆上创建的对象的指针都存放在同一个容器中，将会发生严重的间题。

### 13.2.3 指针的Stash

`Stash`的新版本称为`PStash`，它含有在堆中本来就存在的对象的指针。使用`new`和`delete`，控制指向在堆中创建的对象的指针就变得安全、容易了。

> 代码示例：
[C13_04_PStash.h](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/13.%20Dynamic%20Object%20Creation/C13_04_PStash.h)

```C++
    // C13_04_PStash.h
    #ifndef PSTASH_H
    #define PSTASH_H

    class PStash
    {
        int quantity;   // Number of storage spaces
        int next;       // Next empty space
        // Pointer storage
        void** storage; 
        void inflate(int increase);
    public:
        PStash() : quantity(0), storage(0), next(0) {}
        ~PStash();
        int add(void* element);
        void* operator[](int index) const;
        // Remove the reference from this PStash:
        void* remove(int index);
        // Number of elements in Stash:
        int count() const {return next;}
    };
    #endif //PSTASH_H
```

基本的数据成分是非常相似的，但现在`storage`是一个`void`指针数组，并且用`new`代替`malloc()`为这个数组分配内存。

对象的类型是`void*`，所以这个表达式表示分配了一个`void`指针的数组。析构函数删除`void`指针本身，而不是试图删除它们所指向的内容。

其他方面的变化是用`operator[]`代替了函数`fetch()`，这在语句构成上显得更有意义。因为返回一个`void*`指针，所以用户必须记住在容器内存储的是什么类型，在取回它们时要对这些指针进行类型转换。

> 代码示例：
[C13_04_PStash.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/13.%20Dynamic%20Object%20Creation/C13_04_PStash.cpp)

```C++
    // C13_04_PStash.cpp
    // Pointer Stash definitions
    #include "C13_04_PStash.h"
    #include "../require.h"
    #include <iostream>
    #include <cstring>
    using namespace std;

    int PStash:: add(void* element)
    {
        const int inflateSize = 10;
        if(next >= quantity)
            inflate(inflateSize);
        storage[next++] = element;
        return (next - 1);
    }

    // No ownership:
    PStash::~PStash()
    {
        for(int i = 0; i < next; i++)
        {
            require(storage[i] == 0, "PStash not cleaned up");
            delete []storage;
        }
    }

    // Operator overloading replacement for fetch
    void* PStash::operator[](int index) const
    {
        require(index >= 0, "PStash::operator[] index negative");
        if(index >= next)
            return  0;
        return storage[index];
    }

    void* PStash::remove(int index)
    {
        void* v = operator[](index);
        if(v != 0) storage[index] = 0;
        return v;
    }

    void PStash::inflate(int increase)
    {
        const int psz = sizeof(void*);
        void** st = new void*[quantity + increase];
        memset(st, 0, (quantity + increase) * psz);
        memcpy(st, storage, quantity * psz);
        quantity += increase;
        delete []storage;
        storage = st;
    }
```

`inflate()`的代码被修改为能处理`void*`指针数组的存储，而不是先前的设计，只处理元比特。

## 13.3 用于数组的new和delete

在栈或堆上创建一个对象数组是同样容易的。当然，应当为数组里的每一个对象调用构造函数。但这里有一个限制条件：由于不带参数的构造函数必须被每一个对象调用，所以除了在栈上整体初始化（见第6章）外还必须有一个默认的构造函数。

当使用`new`在堆上创建对象数组时，还必须多做一些操作。下面是一个创建对象数组的例子：`MyType* fp = new MyType[100];`。这样就在堆上为100个`MyType`对象分配了足够的内存并为每一个对象调用了构造函数。但是现在仅拥有一个`MyType*`。这和用下面的表达式创建单个对象得到的结果是一样的：`MyType* fp2 = new MyType;`因为这是我们写的代码，所以我们知道`fp`实际上是一个数组的起始地址。

在销毁数组时，`delete fp2; // OK`和`delete fp; // Not the desire effect`，两个语句看起来一样，但效果却不同。对于`fp`，还有99个析构函数没有调用。因此需要使用`delete []fp;`。

空的方括号告诉编译器产生代码，该代码的任务是将从数组创建时存放在某处的对象数量取回，并为数组的所有对象调用析构函数。

### 13.3.1 使指针更像数组

作为题外话，上面定义的`fp`可以被修改指向任何类型，但这对于一个数组的起始地址来讲没有什么意义。**一般讲来，把它定义为常量会更好些，因为这样任何修改指针的企图都会被认为出错**。比如可以定义为：`int const* q = new int[100];`或`const int* q = new int[100];`。

上面的这两种表达式都把const和被指针指向的int捆绑在一起，而不是指针本身。

如果`int* const q = new int[10];`这样定义，则现在q中的数组元素可以被修改了，但对q本身的修改(例如`q++`)是不合法的，因为它是一个普通数组标识符。

## 13.4 耗尽内存

当`operator new()`找不到足够大的连续内存块来安排对象时，一个
称为`new-handler`的特殊函数将会被调用。首先，检查指向函数的指针，如果指针非0，那么它指向的函数将被调用。

`new-handler`的默认动作是产生一个**异常**(**throw an exception**)。

通过包含`new.h`来替换`new-handler`，然后以想装入的函数地址为参数调用`set_new_handler()`函数。

> 代码示例：
[C13_05_NewHandler.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/13.%20Dynamic%20Object%20Creation/C13_05_NewHandler.cpp)

```C++
    // C13_05_NewHandler.cpp
    // Changing the new-handler

    #include <iostream>
    #include <cstdlib>
    #include <new>
    using namespace std;

    int Count = 0;

    void out_of_memory()
    {
        cerr << "memory exhausted after" << Count
            << " allocations!" << endl;
        exit(1);
    }

    int main()
    {
        set_new_handler(out_of_memory);
        while(1)
        {
            Count++;
            new int[1000];
        }
    }
```

`new-handler`函数必须不带参数且其返回值为`void`。`while`循环将持续分配int对象（并丢掉它们的返回地址）直到空的内存被耗尽。在紧接下去的下一次对`new`的调用时，将没有内存可被调用，所以调用`new-handler`。

## 13.5 重载new和delete

当我们创建一个`new`表达式时，首先会使用`operator new()`分配内存，然后调用构造函数。在`delete`表达式里，调用了析构函数，然后使用`operator delete()`释放内存。