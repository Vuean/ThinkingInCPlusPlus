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

在使用默认参数时必须记住两条规则。第一，只有参数列表的后部参数才是可默认的，也就是说，不可以在一个默认参数后面又跟一个非默认的参数。第二，一且在一个函数调用用中开始使用默认参数，那么这个参数后面的所有参数都必须是默认的（ 这可以从第一条中导出）。

### 7.4.1 占位符参数

函数声明时，参数可以没有标识符，当这些不带标识符的参数用做默认参数时，看起来很有意思。可以这样声明：`void f(int x, int = 0, float = 1.1);`。

在C++中，在函数定义时，并不一定需要标识符，如：`void f(int x, int, float flt) {/*...*/}`。

在函数体中，x和flt可以被引用，但中间的这个参数值则不行，因为它没有名字。调用还必须为这个**占位符**(**placeholder**)提供一个值，有`f(1)`或`f(l,2,3.0)`。这种语法允许把一个参数用做占位符而不去用它。其目的**在于以后可以修改函数定义而不需要修改所有的函数调用**。

当然，用一个有名字的参数也能达到同样的目的，但如果定义的这个参数在函数体内没有使用它，多数编译器会给出一条警告信息，并认为犯了一个逻辑错误。用这种没有名字的参数，我们就可以防止这种警告产生。

## 7.5 选择重载还是默认参数

函数重载和默认参数都给函数调用提供了方便。考虑下面的程序，它用来自动管理内存块。

> 代码示例:
[C7_07_Mem.h](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/7.%20Function%20Overloading%20and%20Default%20Arguments/C7_07_Mem.h)

```C++
    // C07:Mem.h
    #ifndef MEM_H
    #define MEM_H

    typedef unsigned char bytes;

    class Mem
    {
        bytes* mem;
        int size;
        void ensureMinSize(int minSize);
    public:
        Mem();
        Mem(int sz);
        ~Mem();
        int msize();
        bytes* pointer();
        bytes* pointer(int minSize);
    };

    #endif // MEM_H
```

**Mem**对象包括一个**byte**块，以确保有足够的存储空间。默认的构造函数不分配任何的空间。第二个构造函数确保**Mem**对象中有**sz**大小的存储区，析构函数释放空间，**msize()**告诉我们当前**Mem**对象中还有多少字节，**pointer()** 函数产生一个指向存储区起始地址的指针(**Mem**是一个相当底层的工具）。可以有一个重载版本的**pointer()**函数，用这个函数，客户程序员可以将一个指针指向一块内存。该块内存至少有**minSize**大，有成员函数能够做到这一点。

构造造函数和**pointer()**成员函数都使用**private ensureMinSize()**成员函数来增加内存块的大小（请注意，如果内存块要调整的话，存放**pointer()**的结果是不安全的）。

下面实现这个类：

> 代码示例:
[C7_08_Mem.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/7.%20Function%20Overloading%20and%20Default%20Arguments/C7_08_Mem.cpp)

```C++
    // C07:Mem.cpp
    #include "C7_07_Mem.h"
    #include <cstring>
    using namespace std;

    Mem::Mem()
    {
        mem = 0;
        size = 0;
    }

    Mem::Mem(int sz)
    {
        mem = 0;
        size = 0;
        ensureMinSize(sz);
    }

    Mem::~Mem() { delete []mem; }

    void Mem::ensureMinSize(int minsize)
    {
        if(size < minsize)
        {
            bytes* newmem = new bytes[minsize];
            memset(newmem + size, 0, minsize - size);
            memcpy(newmem, mem, size);
            delete []mem;
            mem = newmem;
            size = minsize;
        }
    }

    bytes* Mem::pointer() {return mem;}

    bytes* Mem::pointer(int minSize)
    {
        ensureMinSize(minSize);
        return mem;
    }
```

可以看出，只有函数**ensureMinSize()**负责内存分配，它在第二个构造函数和函数**pointer()**的第二个重载形式中使用。如果**size**足够大的话，函数**ensureMinSize()**什么也不需要做。

设计Mem类的目的是把它作为其他类的一种工具，以简化它们的内存管理，设计一段测试程序，创建一个简单的“string”类：

> 代码示例:
[C7_09_MemTest.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/7.%20Function%20Overloading%20and%20Default%20Arguments/C7_09_MemTest.cpp)

```C++
    // C07:MemTest.cpp
    // Testing the Mem class

    #include "C7_07_Mem.h"
    #include <cstring>
    #include <iostream>
    using namespace std;

    class MyString
    {
        Mem* buf;
    public:
        MyString();
        MyString(char* str);
        ~MyString();
        void concat(char* str);
        void print(ostream& os);
    };

    MyString::MyString() { buf = 0;}

    MyString::MyString(char* str)
    {
        buf = new Mem(strlen(str) + 1);
        strcpy((char*)buf->pointer(), str);
    }

    void MyString::concat(char* str)
    {
        if(!buf) buf  = new Mem;
        strcat((char*) buf->pointer(buf->msize() + strlen(str) + 1),str);
    }

    void MyString::print(ostream& os)
    {
        if(!buf) return;
        os << buf->pointer() << endl; 
    }

    MyString::~MyString() {delete buf;}

    int main()
    {
    MyString s{"my test string"};
    s.print(cout);
    s.concat(" some additional stuff");
    s.print(cout);
    MyString s2;
    s2.concat("Using defalut constructor");
    s2.print(cout); 
    }
```

用这个类，所能做的是创建一个**MyString**，连接文本，打印输出到一个**ostream**中。该类仅仅包含了一个指向**Mem**的指针，但是请注意设置指针为零的默认构造函数和第二个构造函数的区别，**第二个构造函数创建了一个Mem并把一些数据拷贝给它**。使用默认构造函数的好
处，就是可以非常便利地创建空值**MyString**对象的大数组，因为每一个对象只是一个指针，默认构造函数的惟一开销是赋零值。当连接数据时，**MyString**的开销才会开始增长。

另外一方面，考虑一下**Mem**类，如果审视两个构造函数和两个**pointer()**函数时，可以发现：在两种情况下使用默认参数根本不会导致成员函数定义的改变。因此，类的定义可以如下面所示：

> 代码示例:
[C7_10_Mem2.h](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/7.%20Function%20Overloading%20and%20Default%20Arguments/C7_10_Mem2.h)

```C++
    // C07:Mem2.h
    #ifndef MEM2_H
    #define MEM2_H
    typedef unsigned char byte2;

    class Mem
    {
        byte2* mem;
        int size;
        void ensureMinSize(int minSize);
    public:
        Mem(int sz = 0);
        ~Mem();
        int msize();
        byte2* pointer(int minSize = 0);
    };
    #endif // MEM2_H
```

注意：调用**ensureMinSize(0)**总是非常有效。

尽管这两种情况都是基千效率问题作出决定的，但是应该注意不要陷入到只考虑效率的境地（这是诱人的）。**设计类时，最重要的问题是类的接口（客户程序员可以使用的public成员）**。如果产生的类容易使用和重用，那说明成功了。

## 7.6 小结

**不能把默认参数作为一个标志去决定执行函数的哪一块，这是基本原则**。在这种情况下，只要能够，就应该把函数分解成两个或多个重载的函数。一个默认的参数应该是一个在一般情况下放在这个位置的值。这个值出现的可能比其他值要大，所以客户程序员可以忽略它或只在需要改变默认值时才去用它。

默认参数的一个重要应用情况是**在开始定义函数时用了一组参数，而使用了一段时间后发现要增加一些参数**。通过把这些新增参数都作为默认的参数，就可以保证所有使用这一函数的客户代码不会受到影响。
