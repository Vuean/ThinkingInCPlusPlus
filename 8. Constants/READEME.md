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

#### 8.3.2.1 临时量

有时候，在求表达式值期间，编译器必须创建**临时对象**(**temporary object**)。**临时对象会自动地成为常量**。通常接触不到临时对象，改变临时最是错误的，因为这些信息应该是不可得的。

在上述例子中，`f5()`返回一个非`const X`对象，但在表达式`f7(f5());`中，编译器必须产生一个临时对象来保存`f5()`的返回值，使得它能够传递给`f7()`。**如果`f7()`的参数是按值传递的话，它能很好地工作**，然后在`f7()`中形成那个临时量的副本，不会对临时对象`X`产生任何影响。但是，如果`f7()`的参数是按引用传递的，这意味着它取临时对象X的地址，因为`f7()`所带的参数不是按`const`引用传递的，所以它允许对临时对象X进行修改。但是编译器知道：一旦表达式计算结束，该临时对象也会不复存在，因此，对临时对象`X`所作的任何修改也将丢失。由于**把所有的临时对象自动设为`const`**，这种情况导致编译期间错误，因此这种错误不难发现。

然而，下面表达式是合法的：

```C++
    f5() = X(1);
    f5().modify();
```

尽管它们可以编译通过，但实际上存在问题。`f5()`返回一个`X`对象，而且对编译器来说，要满足上面的表达式，**它必须创建临时对象来保存返回值**。于是，在这两个表达式中，临时对象也被修改，表达式被编译过之后，临时对象也将被清除。结果，丢失了所有的修改，从而代码可能存在问题——但是编译器不会有任何提示信息。

### 8.3.3 传递和返回地址

如果传递或返回一个地址（一个指针或一个引用），如果使这个指针或者引用成为`const`，就会阻止客户程序员去取地址井修改其初值。

> 代码示例：
[C8_07_ConstPointer.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/8.%20Constants/C8_07_ConstPointer.cpp)

```C++
    // C8_07_ConstPointer.cpp
    // Constant pointer arg/return

    void t(int*) {}

    void u(const int* cip)
    {
        // *cip = 2;    // Illegal -- modifies value
        int i = *cip;   // OK -- copies value
        // int* ip2 = cip;  // Illegal -- non-const
    }

    const char* v()
    {
        // Returns address of static character array;
        return "result of function v()";
    }

    const int* const w()
    {
        static int i;
        return &i;
    }

    int main()
    {
        int x = 0;
        int* ip = &x;
        const int* cip = &x;
        t(ip);      // OK
        // t(cip); // Not OK

        u(ip);  // OK
        u(cip); // also OK

        // char* cp = v(); // Not OK
        const char* ccp = v(); // OK

        // int* ip2 = w(); // Not OK
        const int* const ccip = w(); // OK
        const int* cip2 = w(); // OK
        // *w() = 1;   // Not OK
    }
```

函数`t()`把一个普通的非`const`指针作为一个参数，而函数`u()`把一个`const`指针作为参数。在函数`u()`里，会看到试图修改`const`指针所指的内容是非法的。编译器也**不允许使用存储在`const`指针里的地址来建立一个非`const`指针**。

函数`v()`返回一个从字符数组的字面值中建立的`const char*`。在编译器建立了它并把它存储在静态存储区之后，这个声明实际上产生这个字符数组的字面值的地址。`w()`的返回值要求这个指针及这个指针所指向的对象均为常量。像函数`v()`一样，仅仅因为它是静态的，所以在函数返回后由`w()`返回的值是有效的。

在`main()`中，函数`t()`将接受一个非`const`指针参数。但是，如果想传给它一个指向`const`的指针，那么将不能防止`t()`会丢下这个指针所指的内容不管，所以编译器会给出一个错误信息。函数`u()`带一个`const`指针， 所以它接受两种类型的参数。这样，带`const`指针参数的函数比不带`const`指针参数的函数更具一般性。

函数`v()`的返回值只可以被赋给一个`const`指针。编译器拒绝把函数`w()`的返回值赋给一个非`const`指针，而接受一个`const int* const`，但令人奇怪的是它也接受一个`const int*`，这与返回类型并不匹配。因为这个值（包含在指针中的地址）正被拷贝，所以自动保持这样的约定：**原始变量不能被改变**。因此，只有当把`const int* const`中的第二个`const`当做一个左值使用时（编译器会阻止这种情况），它才能显示其意义所在。

#### 8.3.3.1 标准参数传递

由于引用的语法（对于调用者它看起来像按值传递）的原因，把一个临时对象传递给接受`const`引用的函数是可能的，但不能把一个临时对象传递给接受指针的函数——对于指针，**它必须明确地接受地址**。所以，按引用传递会产生一个从来不会在C中出现的新的情形：一个总是`const`的临时变量，它的地址可以被传递给一个函数。这就是为什么当临时变量按引用传递给一个函数时，这个函数的参数必须是`const`引用的原因。

> 代码示例：
[C8_08_ConstTemporary.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/8.%20Constants/C8_08_ConstTemporary.cpp)

```C++
    // C8_08_ConstTemporary.cpp
    // Temporaries are const

    class X{};

    X f()
    {
        return X(); // Return by value
    }

    void g1(X&) {}  // Pass by non-const reference

    void g2(const X&) {} // Pass by const reference

    int main()
    {
        // Error: const temporary created by f():
        // cannot bind non-const lvalue reference of type 'X&' to an rvalue of type 'X'
        // g1(f());

        // OK: g2 takes a const reference:
        g2(f());
    }
```

函数`f()`按值返回类`X`的一个对象，这意味着当立即取`f()`的返回值并把它传递给另外一个函数时（如`g1()`和`g2()`函数的调用），将建立一个临时量，该临时量是`const`的。因此，`g1()`函数调用是错误的，因为`g1()`函数不接受`const`引用。

## 8.4 类

**`const`的意思在类里是不同的**。为了保证一个类对象为常量，引进了`const`成员函数：`const`成员函数只能对于`const`对象调用。

### 8.4.1 类里的const

在一个类里使用`const`意味着“在这个对象生命期内，它是一个常量” 。然而，对这个常量来讲，每个不同的对象可以含有一个不同的值。这样，在一个类里建立一个普通的（非`static`的）`const`时，不能给它初值。

#### 8.4.1.1 构造函数初始化列表

**构造函数初始化列表**(**constructor initializer list**)是一个出现在函数参数表和冒号后，但在构造函数主体开头的花括号前的“函数调用列表” ，以提示表里的初始化发生在构造函数的任何代码执行之前。这里是初始化所有`const`的地方，所以类里的`const`的正确形式是：

> 代码示例：
[C8_09_ConstInitialization.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/8.%20Constants/C8_09_ConstInitialization.cpp)

```C++
    // C8_09_ConstInitialization.cpp
    // Initializing const in classes
    #include <iostream>
    using namespace std;

    class Fred
    {
        const int size;
    public:
        Fred(int sz);
        void print();
    };

    Fred::Fred(int sz)
        : size(sz)
    {}

    void Fred::print()
    {
        cout << size << endl;
    }

    int main()
    {
        Fred a(1), b(2), c(3);
        a.print(); b.print(); c.print();
    }
```

#### 8.4.1.2 内部类型的“构造函数”

在构造函数初始化列表里，可以把一个内部类型看成好像它有一个构造函数，就像下面这样：

> 代码示例：
[C8_10_BuiltInTypeConstructors.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/8.%20Constants/C8_10_BuiltInTypeConstructors.cpp)

```C++
    // C8_10_BuiltInTypeConstructors.cpp
    #include <iostream>
    using namespace std;

    class B
    {
        int i;
    public:
        B(int i);
        void print();
    };

    B::B(int ii)
        : i(ii) {}

    void B::print()
    {
        cout << i << endl;
    }

    int main()
    {
        B a(1), b(2);
        float pi(3.1415926);
        a.print();b.print();
        cout << pi << endl;
    }
```

这在初始化`const`数据成员时尤为关键，因为它们必须进入函数体前被初始化。**把一个内部类型封装在一个类里以保证用构造函数初始化**，这是很有用的。例如，下面是一个`Integer`类：

> 代码示例：
[C8_11_EncapsulatingTypes.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/8.%20Constants/C8_11_EncapsulatingTypes.cpp)

```C++
    // C8_11_EncapsulatingTypes.cpp
    #include <iostream>
    using namespace std;

    class IntegerTest
    {
        int i;
    public:
        IntegerTest(int ii = 0);
        void print();
    };

    IntegerTest::IntegerTest(int ii) : i(ii) {}

    void IntegerTest::print()
    {
        cout << i << ' ';
    }

    int main()
    {
        IntegerTest i[10];
        for(int j = 0; j < 10; ++j)
            i[j].print();
    }
```

在`main()`函数中的`IntegerTest`数组元素自动地初始化为零。与`for`循环和`memset()`相比，这种初始化并不必付出更多的开销。

### 8.4.2 编译期间类里的常量

为实现“不管类的对象被创建多少次，都只有一个实例”，这时需要使用关键字`static`，一个内部类型的`static const`可以看做一个编译期间的常最。

**必须在`static const`定义的地方对它进行初始化**。在一个类里创建和使用一个叫做`size`的`static const`，这个类表示一个存放字符串指针的栈。

> 代码示例：
[C8_12_StringStack.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/8.%20Constants/C8_12_StringStack.cpp)

```C++
    // C8_12_StringStack.cpp
    // Using static const to creat a compile-time constant inside a class
    #include <iostream>
    #include <string>
    #include <cstring>
    using namespace std;

    class StringStack
    {
        static const int size = 100;
        const string* stack[size];
        int index;
    public:
        StringStack();
        void push(const string* s);
        const string* pop();
    };

    StringStack::StringStack() : index(0)
    {
        memset(stack, 0, size * sizeof(string*));
    }

    void StringStack::push(const string* s)
    {
        if(index < size)
            stack[index++] = s;
    }

    const string* StringStack::pop()
    {
        if(index > 0)
        {
            const string* rv = stack[--index];
            stack[index] = 0;
            return rv;
        }
        return 0;
    }

    string iceCream [] = {
        "pralines & cream" ,
        "fudge ripple" ,
        "jamocha almond fudge" ,
        "wild mountai n blackberry" ,
        "raspberry sorbet",
        "lemon swirl" ,
        "rocky road" ,
        "deep chocolate fudge"
    };

    const int iCsz = sizeof(iceCream) / sizeof(*iceCream);

    int main()
    {
        StringStack ss;
        for(int i = 0; i < iCsz; ++i)
            ss.push(&iceCream[i]);
        const string* cp;
        while((cp = ss.pop()) != 0)
            cout << *cp << endl;
    }
```

因为`size`用来决定数组`stack`的大小，所以，它实际上是一个编译期间常量，但隐藏在类中。注意`push()`带有一个`const string*`参数，`pop()`返回一个`const string*`，`StringStack`保存`const string*`。否则，就不能用`StringStack`存放在`iceCream`中的指针。

### 8.4.3 const对象和成员函数

**可以用`const`限定类成员函数**。如果声明一个成员函数为`const`，则等于告诉编译器该成员函数可以**为一个`const`对象所调
用**。一个没有被明确声明为`const`的成员函数被看成是将要修改对象中数据成员的函数，而且编译器不允许它为一个`const`对象所调用。

**仅仅声明一个函数在类定义里是`const`的，还不能保证成员函数按声明的方式去做，所以编译器强迫程序员在定义函数时要重申`const`说明**。

要理解声明`const`成员函数的语法，首先注意前面的带`const`的函数声明，它表示函数的返回值是`const`，但这不会产生想要的结果。相反，**必须把修饰符`const`放在函数参数表的后面**。

> 代码示例：
[C8_13_ConstMember.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/8.%20Constants/C8_13_ConstMember.cpp)

```C++
    // C8_13_ConstMember.cpp
    #include <iostream>
    using namespace std;

    class X
    {
        int i;
    public:
        X(int ii);
        int f() const;
    };

    X::X(int ii) : i(ii) {}

    int X::f() const { return i;}

    int main()
    {
        X x1(10);
        const X x2(20);
        cout << x1.f() << endl;
        cout << x2.f() << endl;
    }
```

关键字`const`必须用同样的方式重复出现在定义里，否则编译器把它看成一个不同的函数，因为`f()`是一个`const`成员函数，所以不管它试图以何种方式改变`i`或者调用另一个非`const`成员函数，编译器都把它标记成一个错误。

`cosnt`和非`const`对象调用一个`const`成员函数是安全的。**不修改数据成员的任何函数都应该把它们声明为`const`，这样它可以和`const`对象一起使用。**

> 代码示例：
[C8_14_Quoter.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/8.%20Constants/C8_14_Quoter.cpp)

```C++
    // C8_14_Quoter.cpp
    // Random quote selection
    #include <iostream>
    #include <cstdlib>  // Random number generator
    #include <ctime>    // To seed random generator
    using namespace std;

    class Quoter
    {
        int lastquote;
    public:
        Quoter();
        int lastQuote() const;
        const char* quote();
    };

    Quoter::Quoter()
    {
        lastquote = -1;
        srand(time(0));
    }

    int Quoter::lastQuote() const
    {
        return lastquote;
    }

    const char* Quoter::quote()
    {
        static const char* quotes[] = 
        {
            "Are we having fun yet?",
            "Doctors al ways know best" ,
            "Is it ... Atomic?",
            "Fear is obscene",
            "There is no scientific evidence "
            "to support the idea "
            "that life is seriou s",
            "Things that fDake us happy, make us wise"
        };
        const int qsize = sizeof(quotes) / sizeof(*quotes);
        int qnum = rand() % qsize;
        while(lastquote >= 0 && qnum == lastquote)
            qnum = rand() % qsize;
        return quotes[lastquote = qnum];
    }

    int main()
    {
        Quoter q;
        const Quoter cq;
        cq.lastQuote();
        // cq.quote();  // Illegal, non const function
        for(int i = 0; i < 20; i++)
            cout << q.quote() << endl;
    }
```

构造函数和析构函数都不是`const`成员函数，因为它们在初始化和清除时，总是对对象作些修改。`quote()`成员函数也不能是`const`函数，因为它要修改数据成员`lastquote`。而`lastQuote()`没做修改，所以它可以成为`const`函数，而且也可以被`const`对象`cq`安全地调用。

#### 8.4.3.1 可变的：按位const和按逻辑const

如果想要建立一个`const`成员函数，但仍然想在对象里改变某些数据， 这时该怎么办呢？这关系到**按位(bitwise)const**和**按逻辑(logical)const**（有时也称为**按成员(memberwise)const**）的区别。

按位`const`意思是对象中的每个字节都是固定的，所以对象的每个位映像从不改变。

按逻辑`const`意思是，虽然整个对象从概念上讲是不变的，但是可以以成员为单位改变。 要实现按逻辑`const`的属性，有两种由内部`const`成员函数改变数据成员的方法。

第一种成为**强制转换常量性**(**casting away constness**)。取`this`（这个关键字产生当前对象的地址）并把强制转换成指向当前类型对象的指针。看来`this`已经是所需的指针，但是，在`const`成员函数内部，它实际上是一个`const`指针，所以，还应把它强制转换成一个普通指针，这样就可以在那个运算中去掉常量性。

> 代码示例：
[C8_15_Castway.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/8.%20Constants/C8_15_Castway.cpp)

```C++
    // C8_15_Castway.cpp
    // "Casting away" constness

    class Y
    {
        int i;
    public:
        Y();
        void f() const;
    };

    Y::Y() {i = 0;}

    void Y::f() const
    {
        // 表达式必须是可修改的左值
        // i++; // Error -- const member function
        ((Y*)this)->i++;    // OK -- cast away const-ness
        // Better: use C++ explicit casr syntax
        (const_cast<Y*>(this))->i++; // OK
    }

    int main() 
    {
        const Y yy;
        yy.f();// Actually changes it!
    }
```

常量性的缺乏隐藏在成员函数的定义中，并且没有来自类接口的线索知道对象的数据实际上被修改。为此，应当在类声明里使用关键字`mutable`，以**指定一个特定的数据成员可以在一个`const`对象里被改变**。

> 代码示例：
[C8_16_Mutable.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/8.%20Constants/C8_16_Mutable.cpp)

```C++
    // C8_16_Mutable.cpp
    // The mutable keyword
    #include <iostream>
    class Z
    {
        int i;
        mutable int j;
    public:
        Z();
        void print() const;
        void f() const;
    };

    Z::Z() : i(0), j(0) {}

    void Z::f() const
    {
        // i++;     // Error -- const member function
        j++;
    }

    void Z::print() const
    {
        std::cout << i << " " << j << std::endl;
    }

    int main()
    {
        const Z zz;
        zz.f();
        zz.print();
    }
```

#### 8.4.3.2 只读存储能力

如果一个对象被定义成`const`对象，它就成为被放进只读存储器(ROM)中的候选者，这经常是嵌入式系统程序设计中要考虑做的重要事情。

1) `class`或`struct`必须没有用户定义的构造函数或析构函数。
2) 这里不能有基类，也不能包含有用户定义构造函数或析构函数的成员对象。

## 8.5 volatile

`volatile`的意思是**在编译器认识的范围外，这个数据可以被改变**。可能环境正在改变数据（可能通过多任务、多线程或者中断处理），所以，`volatile`告诉编译器不要擅自作出有关该数据的任何假定，优化期间尤其如此。

> 代码示例：
[C8_17_Volatile.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/8.%20Constants/C8_17_Volatile.cpp)

```C++
    // C8_17_Volatile.cpp
    // The colatile keyword
    class Comm
    {
        const volatile unsigned char byte;
        volatile unsigned char flag;
        enum { bufsize = 100};
        unsigned char buf[bufsize];
        int index;
    public:
        Comm();
        void isr() volatile;
        char read(int index) const;
    };

    Comm::Comm() : index(0), byte(0), flag(0) {}

    // Only a demo; won't actually work as an interrupt service rountine:
    void Comm::isr() volatile
    {
        flag = 0;
        buf[index++] = byte;
        // Wrap to beginning of buffer
        if(index >= bufsize) index = 0;
    }

    char Comm::read(int index) const
    {
        if(index < 0 || index >= bufsize)
            return 0;
        return buf[index];
    }

    int main()
    {
        volatile Comm Port;
        Port.isr();
        // Port.read(0);    // Error -- read() not volatile
    }
```

`volatile`的语法与`const`是一样的，所以对它们的讨论经常被放在一起。为指明可以选择两个中的任何一个，把它们连在一起通称为**c-v限定词**(**c-v qualifier**)。

## 8.6 小结

关键字`const`能将对象、函数参数、返回值和成员函数定义为常量，并能消除预处理器的值替代而不使预处理器的影响。使用所谓的**常量正确性**(**const correctness**)（在任何可能的地方使用`const`）已
成为项目的救星。
