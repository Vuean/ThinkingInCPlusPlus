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
[C4_03_CPPLibTest.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/4.%20Data%20Abstraction/C4_03_CPPLibTest.cpp)

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
[C4_04_Sizeof.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/4.%20Data%20Abstraction/C4_04_Sizeof.cpp)

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

### 4.7.4 头文件的标准

对千包含结构的每个头文件，应当首先检查这个头文件是否已经包含在特定的cpp文件中了，可通过测试预处理器的标记来检查：如果这个标记没有设置，这个文件没有包含，则应当设置它（所以这个结构不会被重声明），并声明这个结构。如果这个标记已经设置，则表明这个类型已经声明了，所以应当忽略这段声明它的代码。

```C++
    #ifndef HEADER_FLAG
    #define HEADER_FLAG
    // Type declaration here...
    #endif // HEADER_FLAG
```

但沿用的可靠标准是大写这个头文件的名字并且用下划线替换句点，如：

```C++
    // C04: Simple.h
    // Simple header that prevents re-definition
    #ifndef SIMPLE_H
    #define SIMPLE_H
    struct Simple
    {
        int i, j, k;
        initialize() {i = j = k = 0;}
    };
    #endif // SIMPLE_H
```

虽然`#endif`之后的`SIMPLE_H`是注释，并且预处理器忽略它，但它对于文档是有用的。防止多次包含的这些预处理器语旬常常称为**包含守卫(include guard)**。

### 4.7.5 头文件中的名字空间

在这本书的几乎所有cpp文件中都有使用**指令(using directive)**描述，通常的形式如下：`using namespace std;`。

但是，在头文件中是决不会看到使用指令的（至少，不在一个范围之外）。原因是，这样的使用指令**去除了对这个特定名字空间的保护**，并且这个结果一直持续到当前编译单元结束。如果将一个使用指令放在一个头文件中（在一个范围之外），这就意味着“名字空间保护”将在包含这个头文件的任何文件中消失，这些文件常常是其他的头文件。这样，如果将使用指令放在头文件中，将很容易最终实际上在各处“关闭”名字空间，因此不能体现名字空间的好处。

简言之，**不要在头文件中放置使用指令**。

### 4.7.6 在项目使用头文件

当用C++建立项目时，我们通常要汇集大量不同的类型（带有相关函数的数据结构）。一般将每个类型或一组相关类型的声明放在一个单独的头文件中，然后在一个处理单元中定义这个类型的函数。当使用这个类型时必须包含这个头文件，执行正确的声明。

## 4.8 嵌套结构

我们可以将一个结构嵌套在另一个结构中，这就可以将相关联的元素放在一起。如下，这个结构用简单链表方式实现了一个**下推栈(push-down stack)**，所以它绝不会越出内存。
> 代码示例
[C4_05_Stack.h](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/4.%20Data%20Abstraction/C4_05_Stack.h)

```C++
    // C04: C4_05_Stack.h
    // Nested struct in linked list
    #ifndef STACK_H
    #define STACK_H

    struct Stack
    {
        struct Link
        {
            void* data;
            Link* next;
            void initialize(void* data, Link* nxt);
        }* head;
        void initialize();
        void push(void* dat);
        void* peek();
        void* pop();
        void cleanup();
    };

    #endif  // STACK_H
```

这个嵌套`struct`称为`Link`，它包括一个指向这个表中的下一个`Link`的指针和一个指向存放在`Link`中的数据的指针。如果`next`指针是零，这就意味着到了表尾。

注意：`head`指针紧接在`struct Link`声明之后定义，而不是单独定义`Link* head`。这是C语言的文法，强调在结构声明之后的分号的重要性，分号表明这个结构类型用逗号分开的定义表结束。

如上所述，嵌套结构具有自己的`initialize()`函数，确保正确的初始化；还有`cleanup()`函数；`push()`函数，取一个指向希望存放的数据（假设已经分配在堆中）的指针；`pop()`函数，返回栈顶的`data`指针并去除栈顶元素（当`pop()`一个元素时，同时销毁由`data`所指的对象）；`peek()`函数，从栈顶返回`data`指针，但是它在栈(Stack)中保留这个栈顶元素。函数定义：

> 代码示例：
[C4_05_Stack.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/4.%20Data%20Abstraction/C4_05_Stack.cpp)

```C++
    // C04: C4_05_Stack.cpp
    // Linked list with nesting
    #include "C4_05_Stack.h"
    #include <iostream>
    using namespace std;

    void Stack::Link::initialize(void* dat, Link* nxt)
    {
        data = dat;
        next = nxt;
    }

    void Stack::initialize() {head = 0;}

    void Stack::push(void* dat)
    {
        Link* newLink = new Link;
        newLink->initialize(dat, head);
        head = newLink;
    }

    void* Stack::peek()
    {
        require(head != 0, "Stack empty");
        return head->data;
    }

    void* Stack::pop()
    {
        if(head == 0) return 0;
        void* result = head->data;
        Link* oldHead = head;
        head = head->next;
        delete oldHead;
        return result;
    }

    void Stack::cleanup()
    {
        require(head == 0, "Stack not empty");
    }
```

### 4.8.1 全局作用域解析

当你要用作用域解析运算符指定一个全局名字时，在运算符前面不加任何东西。下面是一个显示变量和函数的全局作用域解析的例子：
> 代码示例：
[C4_06_Scoperes.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/4.%20Data%20Abstraction/C4_06_Scoperes.cpp)

```C++
    // C04: C4_06_Scoperes.cpp
    // Global scope resolution
    #include <iostream>
    using namespace std;
    int a = 0;

    void f() {}

    struct S{
        int a = 5;
        void f();
    };

    void S::f() {
        ::f();  // Would be recursive otherwise!
        ::a++;  // select the global a
        cout << ::a << endl;
        a--;    // The a at struct scope
        cout << a << endl;
    }

    int main()
    {
        S s;
        s.f();
        f();
    }
```

如果在`S::f()`中没有作用域解析运算符，编译器会默认地选择成员函数的`f()`和`a`。

## 4.9 小结

结构的这种新类型称为**抽象数据类型(abstract data type)**，用这种结构创建的变量称为这个类型的**对象(object)**或**实例(instance)**。调用对象的成员函数称为向这个对象**发消息(sending a message)**。在面向对象的程序设计中的主要动作就是向对象发消息。
