# 8. 第8章 常量

本章重点介绍什么时候、为什么和怎样使用关键字**const**。最后讨论关键字**volatile**，它是**const**的“近亲”（因为它们都关系到变化）并具有完全相同的语法。

**const**的最初动机是取代预处理器#**defines**来进行值替代。从这以后它曾被用于指针、函数变量、返回类型、类对象以及成员函数。

## 8.1 值替代

当用C语言进行程序设计时，预处理器可以不受限制地建立宏并用它来替代值。因为**预处理器只做些文本替代，它既没有类型检查概念，也没有类型检查功能，所以预处理器的值替代会产生一些微小的问题**，这些问题在C++中可以通过使用**const**值而避免。

C中用值替代名字的典型用法是：`#define BUFSIZE 100`，**BUFSIZE**是一个名字，它只是在预处理期间存在，因此它不占用存储空间且能放在一个头文件里，目的是为使用它的所有编译单元提供一个值。

大多数情况，**BUFSIZE**的工作方式与普通变最类似；而且没有类型信息。C++用**const**把值替代带进编译器领域来消除这些问题：`const int bufsize = 100;`。

这样就可以在编译时编译器需要知道这个值的任何地方使用`bufsize`，同时编译器还可以执行**常量折叠**(**constant folding**)，也就是说，编译器在编译时可以通过必要的计算把一个复杂的常量表达式通过缩减简单化。这一点在数组定义里显得尤其重要：`char buf[bufsize];`。

因为预处理器会引入错误，所以我们应该完全用`const`取代`#define`的值替代。

### 8.1.1 头文件里的const

要使用`const`而非`#define`，同样必须把`const`定义放进头文件里。这样，通过包含头文件，可把`const`定义单独放在一个地方并把它分配给一个编译单元。C++中的`const`默认为**内部连接**(**internal linkage**)，也就是说，`const`仅在`const`被定义过的文件里才是可见的，而在连接时不能被其他编译单元看到。当定义一个`const`时，**必须赋一个值给它，除非用extern作出了清楚的说明**：`extern const int bufsize;`。

通常C++编译器并不为`const`创建存储空间，相反它把这个定义保存在它的符号表里。但是，上面的`extern`强制进行了存储空间分配（另外还有一些情况，如取一个`const`的地址，也要进行存储空间分配），由于`extern`意味着使用外部连接，因此必须分配存储空间，这也就是
说有几个不同的编译单元应当能够引用它，所以它必须有存储空间。

### 8.1.2 const的安全性

`const`的作用不仅限于在常数表达式里代替`#defines`。如果用运行期间产生的值初始化一个变量而且知道在变量生命期内是不变的，则用`const`限定该变量是程序设计中的一个很好的做法。

> 代码示例：
[C8_01_Safecons.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/8.%20Constants/C8_01_Safecons.cpp)

```C++
   // C08: Safecons.cpp
    // Using const of safety
    #include <iostream>
    using namespace std;

    const int i = 100;  // Typical constant
    const int j = i + 10; // Value from const expr
    long address = (long)&j;    // Force storage
    char buf[j + 10];   // Still a const expression

    int main()
    {
        cout << "type a character & CR: ";
        const char c = cin.get();   // can't change
        const char c2 = c + 'a';
        cout << c2;
    } 
```

i是一个编译期间的`const`，j是从i中计算出来的，由于i是一个`const`，j的计算值来自一个常数表达式，而它自身也是一个编译期间的`const`。紧接下面的一行需要j的地址，所以迫使编译器给j分配存储空间。即使分配了存储空间，把i值保存在程序的某个地方，由于编译器知道j是`const`, 而且知道j值是有效的，因此，这仍不能妨碍在决定数组`buf`的大小时使用j。

在主函数`main()`里，对于标识符c有另一种`const`，因为其值在编译期间是不知道的。这意味着需要存储空间，而编译器不想保留它的符号表里的任何东西（和C语言的行为一样）。初始化必须在定义点进行，而且一且初始化，其值就不能改变。**如果想让一个值不变，就应该使之成为const。**

### 8.1.3 集合

`const`可以用于集合，但必须保证编译器不会复杂到把一个集合保存到它的符号表中，所以必须分配内存。在这种情况下，`const`意味着**不能改变的一块存储空间**。然而，**不能在编译期间使用它的值**，因为编译器在编译期间不需要知道存储的内容。下面代码是非法的：

> 代码示例：
[C8_02_Constag.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/8.%20Constants/C8_02_Constag.cpp)

```C++
    // C08: Constag.cpp
    // Constents and aggregates
    const int i[] = {1, 2, 3, 4};

    // ! float f[i[3]];     // Illegal
    struct S
    {
        int i, j;
    };

    const S s[] = {{1, 2}, {3, 4}};

    // double d[s[1].j];    // Illegal

    int main()
    {}
```

在一个数组定义里，编译器必须能产生这样的代码，它们移动栈指针来存储数组。在上面这两种非法定义里，编译器给出“提示”是因为它不能在数组定义里找到一个常数表达式。

### 8.1.4 与C语言的区别

**C++默认const是内部连接的**，这样，如果在C++中想完成与C中同样的事情，必须用`extern`明确地把连接改成外部连接：`extern const int bufsize;`。

在C++中，是否为`const`常量创建内存空间依赖于对它如何使用。一般说来，如果一个`const`仅仅用来把一个名字用一个值代替（如同使用`#define`一样），那么该存储空间就不必创建。不过，如果取一个`const`的地址（甚至不知不觉地把它传递给一个带引用参数的函数）或者把它定义成`extern`，则会为该`const`创建内存空间。

在C++中，出现在所有函数之外的`const`的作用域是整个文件（也就是**它只是在该文件外不可见**），也就是说，它**默认为内部连接**。因为C++中的`const`默认为内部连接，所以**不能在一个文件中定义一个`const`，而在另外一个文件中又把它作为`extern`来引用**。为了使`const`成为外部连接以便让另外一个文件可以对它引用，必须明确地把它定义成`extern`。

通过对它进行初始化并指定为`extern`，我们**强迫给它分配内存**（虽然编译器在这里仍然可以选择常批折叠）。**初始化使它成为一个定义而不是一个声明**。在C++中的声明：`extern const int x;`，意味着在别处进行了定义，这也就是为什么C++要求一个`const`定义是需要初始化：**初始化把定义和声明区别开来**。

## 8.2 指针

当使用带有指针的`const`时，有两种选择：**`const`修饰指针正指向的对象，或者`const`修饰在指针里存储的地址**。

### 8.2.1 指向const的指针

定义指针的技巧是**在标识符的开始处读它并从里向外读**。**`const`修饰“最靠近"它的那个**。

例如：`const int* u;`。从标识符开始读：“u是一个指针，指向一个`const int`”。这里不需要初始化，因为u可以指向任何标识符（也就是说，它不是一个const)，但它所指的值是不能被改变的。

### 8.2.2 const指针

使指针本身成为一个`const`指针，必须把`const`标明的部分放在`*`的右边，如:`int d = 1; int* const w = &d;`。可读成：“w是一个指针，这个指针是指向`int`的`const`指针”。

因为指针本身就是`const`指针，所以编译器虚给它一个初始值，这个值在指针声明周期内不变，**但如果需要改变它指向的值是可以的**，可以写成：`*w = 2;`。

结合上述两种写法，可以写出一个`const`指针指向一个`const`对象，下述两种方法都可以，这样**指针和对象都不能改变**：

> 代码示例：

```C++
    int d = 1;
    const int* const x1 = &d;   // (1)
    int const* const x2 = &d;   // (2)
```

> 代码示例：
[C8_03_ConstPointers.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/8.%20Constants/C8_03_ConstPointers.cpp)

```C++
    // C8_03_ConstPointers.cpp
    const int* u;
    int const* v;
    int d = 1;
    int* const w = &d;
    const int* const x1 = &d;
    int const* const x2 = &d;

    int main() {}
```

#### 8.2.2.1 格式

主张：**只要可能，一行只定义一个指针，并尽可能在定义时初始化**。正因为这一点，才可以把`*`“附于”数据类型上：`int* u = &i;`。

### 8.2.3 赋值和类型检查

C++关于类型检查是非常精细的，这一点也扩展到指针赋值。可以把一个非`const`对象的地址赋给一个`const`指针。然而，**不能把一个`const`对象的地址赋给一个非`const`指针**。因为，这样可能通过被赋值的指针改变这个对象的值。当然，**总能用类型转换强制进行这样的赋值**，但是，这是一个不好的程序设计习惯，**打破了对象的`const`属性以及由`const`提供的安全性**。例如：

> 代码示例：
[C8_04_PointerAssignment.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/8.%20Constants/C8_04_PointerAssignment.cpp)

```C++
    // C8_04_PointerAssignment.cpp
    int d = 1;
    const int e = 2;
    int* u = &d;    // OK -- d not const
    // int* v = &e; // Illegal  -- e const
    int* w = (int*)&e;  // legal but bad practice

    int main() {}
```

#### 8.2.3.1 字符数组的字面值

限定词`const`是很严格的，没有强调`const`的地方是字符数组的字面值。如果`char* cp = "howdy";`这样写，也许编译器可以接收并不报错，但是从技术上这是一个错误。因为字符数组的字面值（这里是“howdy”）是被编译器作为一个常量字符数组建立的，**所引用该字符数组得到的结果是它在内存里的首地址**。修改该字符数组的任何字符都会导致运行时错误。

所以字符数组的字面值实际上是常晕字符数组。如果向修改字符串，就需要将其放到一个数组中：`char cp[] = "howdy";`。

## 8.3 函数参数和返回值

如果按常量返回用户定义类型的一个对象的值，这意味着返回值不能被修改。如果传递并返回地址，`const`将保证该地址内容不会被改变。

### 8.3.1 传递const值

如果函数参数是按值传递，则可用指定参数是`const`的，如：

```C++
    void f1(const int i)
    {
        i++;    // Illegal -- compile-time error 
    }
```

在函数里，`const`有这样的意义：**参数不能被改变**。

### 8.3.2 返回const值

如果一个函数的返回值是一个常量(`const`)：`const int g();`。这就约定了函数框架里的原变最不会被修改。

首先，这使`const`看起来没有什么意义。可以从这个例子中看到：按值返回`const`明显失去作用：

> 代码示例：
[C8_05_ConstVal.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/8.%20Constants/C8_05_ConstVal.cpp)

```C++
    // C8_05_ConstVal.cpp
    // Returing consts by value
    // has not meaning for built-in types
    #include <iostream>
    using namespace std;

    int f3()    { return 1;}
    const int f4() { return 1;}

    int main()
    {
        const int j = f3(); // works fine
        int k = f4(); // This works fine too!
        cout << "j = " << j << endl;
        cout << "k = " << k << endl;
    }
```

**对于内部类型来说，按值返回的是否是一个`const`，是无关紧要的，所以按值返回一个内部类型时，应该去掉`const`**，从而不使客户程序员混淆。

**当处理用户定义的类型时，按值返回常量是很重要的**。如果一个函数**按值返回一个类对象为`const`时，那么这个函数的返回值不能是一个左值**（**即它不能被赋值，也不能被修改**）。例如：

> 代码示例：
[C8_06_ConstReturnValues.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/8.%20Constants/C8_06_ConstReturnValues.cpp)

```C++
    // C8_06_ConstReturnValues.cpp
    // Constant return by value
    // Result cannot be used as a lvalue

    class X
    {
        int i;
    public:
        X(int ii = 0);
        void modify();
    };

    X::X(int ii) { i = ii; }

    void X::modify() {i++;}

    X f5()
    {
        return X();
    }

    const X f6()
    {
        return X();
    }

    void f7(X& x)
    {
        // pass by non-const reference
        x.modify();
    }

    int main()
    {
        f5() = X(1);    // OK -- non-const return value
        f5().modify(); // OK

        // cannot bind non-const lvalue reference of type 'X&' to an rvalue of type 'X'
        // f7(f5());       // Causes warning
        // Causes compile-time errors:
        
        // 报错：没有与这些操作匹配的“=”运算符
        // 操作数类型为：const X = X;
        // f6() = X(1);

        // 报错：对象含有与成员函数"X::modify"不兼容的类型限定符
        // 对象类型是：const X
        // f6().modify();
        
        // 报错：将"X&"类型的引用绑定到"const X"类型的初始值设定项时，
        // 限定符被丢弃
        // f7(f6());
    }
```

`f5()`返回一个非`const X`对象，然而`f6()`返回一个`const X`对象。仅仅是非`const`返回值能作为一个左值使用，因此，当按值返回一个对象时，如果不让这个对象作为一个左值使用，则使用`const`很重要。

函数`f7()`把它的参数作为一个非`const`引用，在C++中不能编译通过的原因是会产生一个临时量。