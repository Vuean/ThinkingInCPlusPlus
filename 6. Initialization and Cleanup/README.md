# 6. 初始化与清除

安全性包括初始化和清除两个方面。在C++中，初始化和清除的概念是简化库的使用的关键所在，并可以减少那些在客户程序员忘记去完成这些操作时会引起的细微错误。

## 6.1 用构造函数确保初始化

类的设计者可以通过提供一个叫做**构造函数**(**constructor**)的特殊函数来保证每个对象都被初始化。

构造函数的名字与类的名字一样。这样的函数在初始化时会自动被调用。传递到构造函数的第一个（秘密）参数是this指针，也就是调用这一函数的对象的地址，不过，对构造函数来说，this指针指向一个没有被初始化的内存块，构造函数的作用就是正确的初始化该内存块。

## 6.2 用析构函数确保清除

析构函数的语法与构造函数一样，用类的名字作为函数名。然而析构函数前面加上一个代字号（~），以和构造函数区别。另外，析构函数不带任何参数，因为析构不需任何选项。

> 代码示例:
[C6_01_Constructor.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/6.%20Initialization%20and%20Cleanup/C6_01_Constructor.cpp)

```C++
    // C6_01_Constructor.cpp
    // Constructors & destructors
    #include <iostream>
    using namespace std;

    class Tree
    {
        int height;
    public:
        Tree(int initialHeight);    // Constructor
        ~Tree(); // Destructor
        void grow(int years);
        void printsize();
    };

    Tree::Tree(int initialHeight)
    {
        height = initialHeight;
    }

    Tree::~Tree()
    {
        cout << "inside Tree destructors" << endl;
        printsize();
    }

    void Tree::grow(int years){
        height += years;
    }

    void Tree::printsize()
    {
        cout << "Tree heights is " << height << endl;
    }

    int main()
    {
        cout << "before opening brace: " << endl;
        {
            Tree t(12);
            cout << "after Tree creation" << endl;
            t.printsize();
            t.grow(4);
            cout << "before closing brace: " << endl;
        }
        cout << "after closing brace: " << endl;
    }

    /*
        运行结果：
        before opening brace:
        after Tree creation
        Tree heights is 12
        before closing brace:
        inside Tree destructors
        Tree heights is 16
        after closing brace:
    */
```

可以看到析构函数在包括它的右括号处被调用。

## 6.3 清除定义块

在C++中，对一个对象适用的所有规则，对内部类型的对象也同样适用。这意味着任何类的对象或者内部类型的变量都可以在块的任何地方定义。这也意味着可以等到已经知道一个变量的必要信息时再去定义它，所以总是可以同时定义和初始化一个变量。

> 代码示例:
[C6_02_DefineInitialize.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/6.%20Initialization%20and%20Cleanup/C6_02_DefineInitialize.cpp)

```C++
    // C06: DefineInitialize.cpp
    // Defining variables anywhere
    # include "..\require.h"
    # include <iostream>
    #include <string>
    using namespace std;

    class G
    {
        int i;
    public:
        G(int ii);
    };

    G::G(int ii) { i = ii; }

    int main()
    {
        cout << "initialization value? ";
        int retval = 0;
        cin >> retval;
        require(retval != 0);
        int y = retval + 3;
        G g(y);
    }
```

上例中可以看到先是执行一些代码，然后retval被定义和初始化，接着是一条用来接受客户程序员输入的语句，最后定义y和g。然而，在C中这些变量都只能在块的开始处定义。

一般说来，应该在尽可能靠近变址的使用点处定义变量，并在定义时就初始化，以减少变量在块中的生命周期，减少该变量在块的其他地方被误用的机会。

### 6.3.1 for循环

```C++
    for(int j = 0; j < 100; j++)
        cout << "j = " << j << endl;
    for(int i = 0; i < 100; i++)
        cout << "i = " << i << endl;
```

变量i和j都是在for表达式中直接定义的（在C中不能这样做），然后它们就可以作为一个变量在for循环中使用。

要注意局部变量会屏蔽其封闭块内的其他同名变量。通常，使用与全局变量同名的局部变量会使人产生误解， 并且也易于产生错误。

### 6.3.2 内存分配

一个变量可以在某个程序范围内的任何地方定义，所以在这个变量的定义之前是无法对它分配内存空间的。即使存储空间在块的一开始就被分，构造函数也仍然要到对象的定义时才会被调用，因为标识符只有到此时才有效。

> 代码示例
[C6_03_Nojump.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/6.%20Initialization%20and%20Cleanup/C6_03_Nojump.cpp)

```C++
    // C06: Nojump.cpp
    // Can't jump past constructors

    class X
    {
    public:
        X();
    };

    X::X() {}

    void f(int i)
    {
        if (i < 10)
        {
            // !goto jumpl; // error: goto bypass init
        }
        X x1;   // Constructor called here
        jumpl:
        switch (i)
        {
            case 1:
                X x2;
                break;
            case 2:
                X x3;
                break;
        }
    }

    int main()
    {
        f(9);
        f(11);
    }
```

这里讨论的内存分配都是在堆栈中进行的。内存分配是通过编译器向下移动堆栈指针来实现的（这里的“向下”是相对而言的，实际指针值增加，还是减少，取决于机器）。也可以在堆栈中使用new为对象分配内存。

## 6.4 带有构造函数和析构函数的Stash

建立带有构造函数和析构函数的Stash头文件。

> 代码示例：
[C6_04_Stash2.h](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/6.%20Initialization%20and%20Cleanup/C6_04_Stash2.h)

```C++
    // C06: Stash2.h
    // With Constructors and Destructors
    #ifndef STASH2_H
    #define STASH2_H

    class Stash
    {
        int size;           // Size of each space
        int quantity;       // Number of storage spaces
        int next;           // Next empty space
        // Dynamically allocated array of bytes:
        unsigned char* storage;
        void inflate(int increase);     // inflate：使充气，使膨胀
    public:
        Stash(int size);
        ~Stash();
        int add(void* element);
        void* fetch(int index);         // fetch：取，拿
        int count();
    };

    #endif // STASH2_H
```

以下为实现文件，用构造函数和析构函数分别代替了initialize()和cleanup()函数。

> 代码示例：
[C6_05_Stash2.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/6.%20Initialization%20and%20Cleanup/C6_05_Stash2.cpp)

```C++
    // C06:Stash2.cpp
    // Constructors & destructors
    #include "C6_04_Stash2.h"
    #include "../require.h"
    #include <iostream>
    #include <cassert>
    using namespace std;
    const int increment = 100;

    Stash::Stash(int sz)
    {
        size = sz;
        quantity = 0;
        storage = 0;
        next = 0;
    }

    int Stash::add(void* element)
    {
        if(next >= quantity)    // Enough space left?
            inflate(increment);
        // Copy element into storage
        // starting at next empty space:
        int startBytes = next * size;
        unsigned char* e = (unsigned char*) element;
        for (int i = 0; i < size; i++)
            storage[startBytes + i] = e[i];
        next++;
        return (next - 1);  // Index number
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

    Stash::~Stash()
    {
        if(storage != 0)
        {
            cout << "freeing storage" << endl;
            delete [] storage;
        }
    }
```

在下面测试程序中，**Stash**对象的定义放在紧靠使用对象的地方，对象的初始化通过构造函数的参数列表来实现，而对象的初始化似乎成了对象定义的一部分。

> 代码示例
[C6_06_Stash2Test.cpp]()

```C++
    // C6: Stash2Test.cpp
    #include "C6_04_Stash2.h"
    #include "../require.h"
    #include <iostream>
    #include <fstream>
    #include <string>
    using namespace std;

    int main()
    {
        Stash intStash(sizeof(int));
        for(int i = 0; i < 100; ++i)
            intStash.add(&i);
        for(int j = 0; j < intStash.count(); ++j)
            cout << "intStash.fetch(" << j << ") = "
                << *(int*) intStash.fetch(j)
                << endl;
        const int bufsize = 80;
        Stash stringStash(sizeof(char) * bufsize);
        ifstream in("C6_06_Stash2Test.cpp");
        assure(in, " C6_06_Stash2Test.cpp");
        string line;
        while(getline(in, line))
        {
            stringStash.add((char*)line.c_str());
        }
        int k = 0;
        char* cp;
        while((cp = (char*)stringStash.fetch(k++)) != 0)
            cout << "stringStach.fetch(" << k << ") = " << cp << endl;
    }
```

## 6.5 带有构造函数和析构函数的Stack

重新实现含有构造函数和析构函数的链表（在Stack内），看看使用new和delete时，构造函数和析构函数怎样巧妙地工作。

> 代码示例：
[C6_07_Stack3.h]()

```C++
    // C06: Stack3.h
    // With Constructors and Destructors
    #ifndef STACK3_H
    #define STACK3_H

    class Stack
    {
        struct Link
        {
            void* data;
            Link* next;
            Link(void* dat, Link* nxt);
            ~Link();
        }* head;
    public:
        Stack();
        ~Stack();
        void push(void* dat);
        void* peek();
        void* pop();
    };
    #endif // STACK3_H
```

> 代码示例：
[C6_08_Stack3.cpp]()

```C++
    // C06: Stack3.cpp
    #include "C6_07_Stack3.h"
    #include "../require.h"
    using namespace std;

    Stack::Link::Link(void* dat, Link* nxt)
    {
        data = dat;
        next = nxt;
    }

    Stack::Link::~Link() { }

    Stack::Stack() { head = 0;}

    void Stack::push(void* dat)
    {
        head = new Link(dat, head);
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

    Stack::~Stack()
    {
        require(head == 0, "Stack not empty");
    }
```

构造函数`Link::Link()`只是简单的初始化**data指针**和**next指针**，所以在`Stack::push()`为一个新的链表分配内存，并初始化该对象的指针成员。

如果**Link**的析构函数删除**data**指针，`pop()`将最终返回一个指向被删除对象的指针，很明显，这会引起错误。`Link`和`Stack`仅仅存放指针，但它们不负责清除这些指针。

所以知道谁来负责清除一个对象，对于一个程序是成功还是失败来说是很关键的——这就是为什么如果`Stack`对象销毁时不为空，`Stack::~Stack()`就会打印出错误信息的原因。

因为分配和清除`Link`对象的实现隐藏在类`Stack`中，它是内部实现的一部分，所以在测试程序中看不到它运行的结果，尽管从`pop()`返回的指针由我们负责删除。

> 代码示例：
[C6_09_Stack3Test.cpp]()

```C++
    // C06:Stack3Test.cpp
    #include "C6_07_Stack3.h"
    #include "../require.h"
    #include <iostream>
    #include <fstream>
    #include <string>
    using namespace std;

    int main(int argc, char* argv[])
    {
        requireArgs(argc, 1);   // File name is argument
        ifstream in(argv[1]);
        assure(in, argv[1]);
        Stack textlines;
        string line;
        // Read file and store lines in the stack:
        while(getline(in, line))
            textlines.push(new string(line));
        // Pop the lines from the stack and print them:
        string* s;
        while((s = (string*)textlines.pop()) != 0)
        {
            cout << *s << endl;
            delete s;
        }
    }
```

`textlines`中的所有行被弹出和删除，但是如果不出现这些操作的话， 就会得到由`require()`带回的信息，这些信息表明这里有内存泄漏。

## 6.6 集合初始化

