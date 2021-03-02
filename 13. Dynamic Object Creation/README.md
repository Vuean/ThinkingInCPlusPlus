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

在特殊的情形下，`new`和`delete`并不能满足需要。最常见的改变分配系统的原因是出于效率考虑：也许要创建和销毁一个特定的类的非常多的对象以至于这个运算变成了速度的瓶颈。

另一个问题是堆碎片：分配不同大小的内存可能会在堆上产生很多碎片，以至于很快用完内存。

当重载`operator new()`和`operator delete()`时，我们只是改变了原有的内存分配方法，记住这一点是很重要的。

### 13.5.1 重载全局new和delete

重载的`new`必须有一个`size_t`参数。这个参数由编译器产生并传递给
我们，它是要分配内存的对象的长度。必须返回一个指向等于这个长度（或大于这个长度，如果有这样做的原因）的对象的指针，如果没有找到存储单元（在这种情况下，构造函数不被调用），则返回一个0。然而如果找不到存储单元，不能仅仅返回0，也许还应该做一些诸如调用`new-handler`或产生一个异常信息之类的事，通知这里存在问题。

`operator new()`的返回值是一个`void*`，而不是指向任何特定类型的指针。所做的是分配内存，而不是完成一个对象建立一直到构造函数调用了才完成对象的创建，它是编译器确保做的动作，不在我们的控制范围之内。

`operator delete()`的参数是一个指向由`operator new()`分配的内存的`void*`。参数是一个`void*`是因为它是在调用析构函数后得到的指针。析构函数从存储单元里移去对象。`operator delete()`的返回类型是`void`。

> 代码示例：
[C13_06_GlobalOperatorNew.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/13.%20Dynamic%20Object%20Creation/C13_06_GlobalOperatorNew.cpp)

```C++
    // C13_06_GlobalOperatorNew.cpp
    // Overload global new/operator

    #include <cstdio>
    #include <cstdlib>
    using namespace std;

    void* operator new(size_t sz)
    {
        printf("operator new: %d Bytes\n", sz);
        void* m = malloc(sz);
        if(!m) puts("out of memory");
        return m;
    }

    void operator delete(void* m)
    {
        puts("operator delete");
        free(m);
    }

    class S
    {
        int i[100];
    public:
        S() {puts("S::S()");}
        ~S() {puts("S::~S()");}
    };

    int main()
    {
        puts("creating & destorying an int");
        int* p = new int(47);
        delete p;
        puts("creating destorying an s");
        S* s = new S;
        delete s;
        puts("creating & destorying S[3]");
        S* sa = new S[3];
        delete []sa;
    }
```

注意，这里使用`printf()`和`puts()`而不是`iostreams`。因此，当创建了一个`iostream`对象时（像全局的`cin`、`cout`和`cerr`），它们调用`new`去分配内存。用`printf()`不会进入死锁状态，因为它不调用`new`来初始化本身。

### 13.5.2 对于一个类重载new和delete

为一个类重载`new`和`delete`时，尽管不必显式地使用`static`，但实际上仍是在创建`static`成员函数。

在下面的例子里为类`Framis`创建了一个非常简单的内存分配系统。程序开始时在静态数据区域留出一块存储单元。这块内存被用来为`Framis`类型的对象分配存储空间。为了标明哪块存储单元已被使用，这里使用了一个字节(`byte`)数组，一个字节代表一块存储单元。

> 代码示例：
[C13_07_Framis.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/13.%20Dynamic%20Object%20Creation/C13_07_Framis.cpp)

```C++
    // C13_07_Framis.cpp
    // Local overload new & delete

    #include <cstddef>
    #include <fstream>
    #include <iostream>
    #include <new>
    using namespace std;
    ofstream out("Framis.out");

    class Framis
    {
        enum {sz = 10};
        char c[sz]; // To take up space, not used
        static unsigned char pool[];
        static bool alloc_map[];
    public:
        enum { psize = 100 };   // framis allowed
        Framis() {out << "Framis()\n"; }
        ~Framis() {out << "~Framis()\n"; }
        void* operator new(size_t) throw(bad_alloc);
        void operator delete(void*);
    };

    unsigned char Framis::pool[psize* sizeof(Framis)];
    bool Framis::alloc_map[psize] = {false};

    void* Framis::operator new(size_t) throw(bad_alloc)
    {
        for(int i = 0; i < psize; i++)
        {
            if(!alloc_map[i])
            {
                out << "using block " << i << " ... ";
                alloc_map[i] = true;
                return pool + (i * sizeof(Framis));
            }
            out << "out of memory" << endl;
            throw bad_alloc();
        }
    }

    void Framis::operator delete(void* m)
    {
        if(!m) return;
        unsigned long block = (unsigned long)m - (unsigned long)pool;
        block /= sizeof(Framis);
        out << "freeing block " << block << endl;
        alloc_map[block] = false;
    }

    int main()
    {
        Framis* f[Framis::psize];
        try
        {
            for(int i = 0; i < Framis::psize; i++)
                f[i] = new Framis;
            new Framis;
        } catch(bad_alloc){
            cerr << "Out of memory" << endl;
        }
        delete f[10];
        f[10] = 0;
        Framis* x = new Framis;
        delete x;
        for(int j = 0; j < Framis::psize; j++)
            delete f[j];
    }
```

局部`operator new()`和全局`operator new()`具有相同的语法。首先对分配表进行搜索，寻找值为`false`的成员。找到后将该成员设置为`ture`，以此声明对应的存储单元已经被分配了，并且返回这个存储单元的地址。如果找不到任何空闲内存，将会给跟踪文件发送一个消息，并且
产生一个`bad_alloc`类型的异常信息。

### 13.5.3 为数组重载new和delete

如果为一个类重载了`operator new()`和`operator delete()`，那么无论何时创建这个类的一个对象都将调用这些运算符。但如果要创建这个类的一个对象数组时，全局`operator new()`就会被立即调用，用来为这个数组分配足够的内存。对此，可以通过为这个类重载运算符的数组版本，即`operator new[]`和`operator delete[]`，来控制对象数组的内存分配。

> 代码示例：
[C13_08_ArrayOperatorNew.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/13.%20Dynamic%20Object%20Creation/C13_08_ArrayOperatorNew.cpp)

```C++
    // C13_08_ArrayOperatorNew.cpp
    // operator new for arrays

    #include <new>
    #include <fstream>
    using namespace std;
    ofstream trace("ArrayOperatorNew.out");

    class Widget
    {
        enum {sz = 10};
        int i[sz];
    public:
        Widget() {trace << "*"; }
        ~Widget(){trace << "~"; }
        void* operator new(size_t sz)
        {
            trace << "Widget::new: " << sz << " bytes" << endl;
            return ::new char[sz];
        }
        void operator delete(void* p)
        {
            trace << "Widget::delete: " << endl;
            return ::delete []p;
        }
        void* operator new(size_t sz)
        {
            trace << "Widget::new[]: " << sz << " bytes" << endl;
            return ::new char[sz];
        }
        void operator delete[](void* p)
        {
            trace << "Widget::delete[]: " << endl;
            return ::delete []p;
        }
    };

    int main()
    {
        trace << "new widget" << endl;
        Widget* w = new Widget;
        trace << "\ndelete Widget" << endl;
        delete w;
        trace << "\nnew widget[25]" << endl;
        Widget* wa = new Widget[25];
        trace << "\ndelete []Widget" << endl;
        delete []wa;
    }
```

### 13.5.4 构造函数调用

分析语句：`MyType* f = new MyType;`，调用`new`分配了一个大小等于`MyType`类型的内存，然后在那个内存上调用了`MyType`构造函数。但如果使用了`new`的内存分配没有成功，将会出现什么状况呢？在那种情况下，构造函数不会被调用，所以虽然没能成功地创建对象，但至少没有调用构造函数并传给它一个为0的`this`指针。

> 代码示例：
[C13_09_NoMemory.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/13.%20Dynamic%20Object%20Creation/C13_09_NoMemory.cpp)

```C++
    // C13_09_NoMemory.cpp
    // Constructor isn't called if new fails
    #include <iostream>
    #include <new>
    using namespace std;

    class NoMemory
    {
    public:
        NoMemory()
        {
            cout << "NoMemory::NoMemory()" << endl;
        }
        void* operator new(size_t sz) throw(bad_alloc)
        {
            cout << "NoMemory::operator new" << endl;
            throw bad_alloc();
        }
    };

    int main()
    {
        NoMemory* nm = 0;
        try{
            nm = new NoMemory();
        }catch(bad_alloc)
        {
            cerr << "out of memory exception" << endl;
        }
        cout << "nm = " << nm << endl;
    }
```

当程序运行时，并没有打印出构造函数的信息，仅仅是打印了`operator new()`和异常处理的信息。因为`new`没有返回，构造函数也没有被调用，当然它的信息就不会被打印出来。

### 13.5.5 定位new和delete

重载`operator new()`还有其他两个不常见的用途。

1. 我们也许会想在内存的指定位置上放置一个对象。这对于面向硬件的内嵌系统特别重要，在这个系统中，一个对象可能和一个特定的硬件是同义的。
2. 我们也许会想在调用`new`时，能够选择不同的内存分配方案。

这两个特性可以用相同的机制实现：重载的`operator new()`可以带一个或多个参数。正如前面所看到的，第一个参数总是对象的长度，它在内部计算出来并由编译器传递给new。但其他参数可由我们自己定义：一个放置对象的地址、一个是对内存分配函数或对象的引用，或其他任何使我们方便的设置。

例如：`X* xp = new(a) X;`，将a作为第二个参数传给`operator new()`。

> 代码示例：
[C13_10_PlacementOperatorNew.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/13.%20Dynamic%20Object%20Creation/C13_10_PlacementOperatorNew.cpp)

```C++
    // C13_10_PlacementOperatorNew.cpp
    // Placement with operator new()
    #include <cstddef>
    #include <iostream>
    using namespace std;

    class X
    {
        int i;
    public:
        X(int ii = 0) : i(ii)
        {
            cout << "this = " << this << endl;
        }
        ~X()
        {
            cout << "X::~X(): " << this << endl;
        }
        void* operator new(size_t, void* loc)
        {
            return loc;
        }
    };

    int main()
    {
        int l[10];
        cout << "l = " << l << endl;
        X* xp = new(l) X(47);   // X at location l
        xp->X::~X();    // Explicit destructor call
    }
```

注意：`operator new()`仅返回了传递给它的指针。因此，调用者可以决定将对象存放在哪里，这时在该指针所指向的那块内存上，作为new表达式一部分的构造函数将被调用。

在销毁对象时将会出现两难选择的局面。因为仅有一个版本的`operator delete`，所以没有办法说“对这个对象使用我的特殊内存释放器”。可以调用析构函数，但不能用动态内存机制释放内存，因为内存不是在堆上分配的。解决方法是用非常特殊的语法：我们可以显式地调用析构函数。