# 第10章 名字控制

C++允许我们对名字的产生和名字的可见性进行控制，包括这些名字的存储位置以及名字的连接。关于`static`的所有使用最基本的概念是指“位置不变的某个东西”，不管这里是指在内存中的物理位置还是指在文件中的可见性。

在本章里，我们将看到`static`如何控制存储和可见性，还将看到一种通过C++的**名字空间**特征来控制访问名字的改进方法。

## 10.1 来自C语言中的静态元素

在C和C++中，`static`都有两种基本的含义，并且这两种含义经常是互相冲突的：

1) 在固定的地址上进行存储分配，也就是说对象是在一个特殊的**静态数据区**(**static data area**)上创建的，而不是每次函数调用时在堆栈上产生的。这也是静态存储的概念。
2) 对一个特定的编译单位来说是局部的。这样，`static`控制名字的**可见性**(**visibility**)，所以这个名字在这个单元或类之外是不可见的。这也描述了连接的概念，它决定连接器将看到哪些名字。

### 10.1.1 函数内部的静态变量

通常，在函数体内定义一个局部变最时，编译器在每次函数调用时使堆栈的指针向下移一个适当的位置，为这些局部变量分配内存。有时想在两次函数调用之间保留一个变量的值，可以在函数内部定义一个`static`对象，这个对象将存储在程序的静态数据区中，而不是堆栈中。这个变量**只在函数第一次调用时初始化一次**，以后它将在两次函数调用之间保持它的值。

> 代码示例：
[C10_01_StaticVAriablesInFunctions.cpp]()

```C++
    // C10_01_StaticVAriablesInFunctions.cpp
    #include "../require.h"
    #include <iostream>
    using namespace std;

    char oneChar(const char* charArray = 0)
    {
        static const char* s;
        if(charArray)
        {
            s = charArray;
            return *s;
        }
        else
        {
            require(s, "un-initialized s");
        }
        if(*s == '\0')
            return 0;
        return *s++;
    }

    char* a = "abcdefghijklmnopqrstuvwxyz";

    int main()
    {
        oneChar(a); // initializes s to a 
        char c;
        while((c = oneChar()) != 0)
            cout << c << endl;
    }
```