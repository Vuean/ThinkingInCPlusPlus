# 第三章 C++中的C

本章对C的构造和C++的一些基本结构作简要介绍。

## 3.1 创建函数

标准C和C++有一个特性叫做**函数原型(function prototyping)**。用函数原型，在声明和定义一个函数时，必须使用参数类型描述。在函数原型中，参数表包含了应当传递给函数的参数类型和参数标识符（对声明而言可以是任选的）。如：

```C++
    int translate(float x, float y, float z);
```

同时以下形式也是可以接受的，因为在调用函数时，编译器只是检查类型。：

```C++
    int translate(float, float, float);
```

C和C++有两种其他声明参数列表的方式。一是空参数列表。二是不确定参数列表。

其中，“空参数列表”，在 **C++** 中可声明为`func()`，即表示函数`func`有 0 个参数；但是在 **C** 中却意味着**不确定的参数数目**。在C和C++中，声明 `func(void)` 都意味着空的参数列表。

“可变的参数列表”，可用省略号{...}表示。如果不想使用函数原型的错误检查功能，可以对有固定参数表的函数使用可变参数列表。

### 3.1.1 函数返回值

C++函数原型必须知名函数的返回值类型。如果没有返回值，可以使用void关键字。

```C++
    int f1(void);   // Returns an int, takes no arguments
    int f2();       // Like f1() in C++ but not in Standard C
    float f3(float, int, char, double); // Returns a float
    void f4(void); // Takes no arguments,returns nothing
```

要从一个函数返回值，必须使用 `return` 语句。`return` 语句退出函数返回到函数调用后的那一点。在一个函数定义中可以有多个 `return` 语句。

> 代码示例：
[01_Return.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/3.%20The%20C%20in%20C%2B%2B/01_Return.cpp)

```C++
    // C03: Return.cpp
    // Use of "return"

    #include <iostream>
    using namespace std;

    char cfunc(int i)
    {
        if (0 == i)
        {
            return 'a';
        }
        if(1 == i)
        {
            return 'g';
        }
        if (5 == i)
        {
            return 'z';
        }
        return 'c';
    }

    int main()
    {
        cout << "type an integer: ";
        int val;
        cin >> val;
        cout << cfunc(val) << endl;
        return 0;
    }
```

### 3.1.2 使用C的函数库

在C++编程中，当前C函数库中的所有函数都可以使用。

### 3.1.3 通过库管理器创建自己的库

我们可以将自己的函数收集到一个库中。大多数编程包带有一个库管理器来管理对象模块组。如果想创建一个库，那么就建立一个头文件，它包含库中的所有函数原型。把这个头文件放置在预处理器搜索路径中的某处，或者在当前目录中（以便能被`#include“头文件”`发现），或者在包含路径中（以便能被`#include<头文件>`发现）。

## 3.2 执行控制语句

C++使用C的所有执行控制语句。包括`if-else`、`while`、`do-while`、`for`和`switch`选择语句。

### 3.2.1 真和假

所有的条件语句都使用条件表达式的真或假来判定执行路径。

### 3.2.2 if-else语句

`if-else` 语句有两种形式：用 `else` 或不用 `else`。这两种形式是：

```C++
    if(表达式)
        语句
    或
    if(表达式)
        语句
    else
        语句
```

“表达式”的值为真或假。“语句”是一个以分号结束的简单语句，或一组包含在大括号里的简单语句构成的一个符合语句。

> 代码示例：
[02_IfElse.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/3.%20The%20C%20in%20C%2B%2B/02_IfElse.cpp)

```C++
    // C03: IfElse.cpp
    // Demonstration of if and if-else conditionals

    #include<iostream>
    using namespace std;

    int main()
    {
        int i;
        cout << "type a number and 'Enter'" << endl;
        cin >> i;

        if(i > 5)
            cout << "It's greater than 5" << endl;
        else if(i < 5)
            cout << "It's less than 5" << endl;
        else
            cout << "It's equal to 5" << endl;

        cout << "type a number and 'Enter'" << endl;
        cin >> i;
        if(i < 10)
        {
            if (i > 5)// "if" is just another statement
                cout << "5 < i < 10" << endl;
            else
                cout << "i <= 5" << endl;
        }
        else
            cout << "i >= 10" << endl;

        return 0;
    }
```

### 3.2.3 while语句

`while`、`do-while`、`for`语句是循环控制语句。一个语句重复执行直到控制表达式的计值为假。

`while` 循环一开始就对表达式进行计算，并在每次重复执行语句之前再次计算。其形式是：

```C++
    while(表达式)
        语句
```

> 代码示例：
[03_Guess.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/3.%20The%20C%20in%20C%2B%2B/03_Guess.cpp)

```C++
    // C03: 03_Guess.cpp
    // Guess a number (demonstrates "while")

    #include <iostream>
    using namespace std;

    int main()
    {
        int secret = 15;
        int guess = 0;
        while( guess != secret ){
            cout << "guess the number: ";
            cin >> guess;
        }
        cout << "You guessed it!" << endl;
        return 0;
    }
```

### 3.2.4 do-while语句

`do-while` 的形式是：

```C++
    do
        语句
    while(表达式)
```

`do-while` 语句与 `while` 语句的区别在于，`do-while` 语句即使表达式第一次计值就为假，前面的语句也至少执行一次。在一般的 `while` 语句中，如果条件第一次为假，语句一次也不会执行。

> 代码示例：
[04_Guess2.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/3.%20The%20C%20in%20C%2B%2B/04_Guess2.cpp)

```C++
    // C03: 04_Guess.cpp
    // The guess program using do-while

    #include <iostream>
    using namespace std;

    int main()
    {
        int secret = 15;
        int guess; // No initialization needed here
        do{
            cout << "guess the number: ";
            cin >> guess;
        } while(guess != secret);
        cout << "You got it!" << endl;
        return 0;
    }
```

### 3.2.5 for语句

在第一次循环前，`for` 循环执行初始化。然后它执行条件测试，并在每一次循环结束时执行某种形式的“步进”。`for` 循环的形式是：

```C++
    for(initialization; conditional; step)
        语句
```

`for` 循环常用于“计数”任务：
> 代码示例：
[05_Charlist.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/3.%20The%20C%20in%20C%2B%2B/05_Charlist.cpp)

```C++
    // C03: 05_Charlist.cpp
    // Display all the ASCII characters

    #include <iostream>
    using namespace std;

    int main()
    {
        for(int i = 0; i < 128; i++)
        {
            if(i != 26) // ANSI Terminal Clear screen
                cout << "value: " << i << " characters "
                    << char(i) // Type conversion
                    << endl;
        }
        return 0;
    }
```

### 3.2.6 关键字break和continue

在任何一个`while`、`do-while` 或 `for` 循环的结构体中，都能够使用 `break` 和 `continue` 控制循环的流程。`break` 语句**退出循环，不再执行循环中的剩余语句**。`continue` 语句**停止执行当前的循环，返回到循环的起始处开始新的一轮循环**。
> 代码示例：
[06_Menu.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/3.%20The%20C%20in%20C%2B%2B/06_Menu.cpp)

```C++
    // C03: 06_Menu.cpp
    // Simple menu program demostrating

    #include <iostream>
    using namespace std;

    int main()
    {
        char c;
        while(true){
            cout << "MAIN MENU" << endl;
            cout << "l: left, r: right, q: quit -> ";
            cin >> c;
            if(c == 'q')
                break;  // Out of while(true)
            if(c == 'l'){
                cout << "LEFT MENU:" << endl;
                cout << "select a or b: ";
                cin >> c;
                if(c == 'a'){
                    cout << "you chose 'a'." << endl;
                    continue;   // Back to main menu
                }
                if(c == 'b'){
                    cout << "you chose 'b'." << endl;
                    continue; // Back to main menu
                }
                else{
                    cout << "you didn't choose a or b!" << endl;
                    continue; // Back to main menu
                }
            }
            if(c == 'r'){
                cout << "RIGHT MENU:" << endl;
                cout << "select c or d: ";
                cin >> c;
                if(c == 'c'){
                    cout << "you chose 'c'." << endl;
                    continue;   // Back to main menu
                }
                if(c == 'd'){
                    cout << "you chose 'd'." << endl;
                    continue; // Back to main menu
                }
                else{
                    cout << "you didn't choose 'c' or 'd'." << endl;
                    continue; // Back to main menu
                }
            }
            cout << "you must type l or r or q!" << endl;
        }
        cout << "quitting menu..." << endl;
        return 0;
    }
```

其中，`while(true)` 语句等价于“永远执行这个循环”。当用户选择‘q’时，`break` 语句使程序跳出这个无限循环。

### 3.2.7 switch语句

`switch` 语句根据一个**整型表达式**的值从几段代码中选择执行。它的形式是：

```C++
    switch(selector){
    case integral-valuel: statement; break;
    case integral-value2: statement; break;
    case integral-value3: statement; break;
    case integral-value4: statement; break;
    case integral-value5: statement; break;
    (...)
    default: statement;
```

选择器(selector)是一个产生整数值的表达式。`switch` 语句把选择器(selector)的结果和每一个整数值(integral-value)比较。如果发现匹配，就执行对应的语句（简单语句或复合语句）。如果都不匹配，则执行`default`语句。

其中，`break` 是可选得，如果省略它，`case` 语句会顺序执行它后面的语句。

> 代码示例：
[07_Menu2.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/3.%20The%20C%20in%20C%2B%2B/07_Menu2.cpp)

```C++
    // C03:07_Menu2.cpp
    // A menu  using a switch statement

    #include <iostream>
    using namespace std;

    int main()
    {
        bool quit = false;
        while (quit == false){
            cout << "Select a, b, c or q to quit: ";
            char response;
            cin >> response;
            switch(response){
                case 'a' : cout << "you choose 'a'" << endl;
                        break;
                case 'b' : cout << "you choose 'b'" << endl;
                        break;
                case 'c' : cout << "you choose 'c'" << endl;
                        break;
                case 'q' : cout << "quitting menu" << endl;
                        quit = true;
                        break;
                default: cout << "Please use a, b, c or q!" << endl;
            }
        }
        return 0;
    }
```

### 3.2.8 使用和滥用goto

`goto` 是一种不好的编程方式，经常避免使用 `goto`。

> 代码示例：
[08_gotoKeyword.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/3.%20The%20C%20in%20C%2B%2B/08_gotoKeyword.cpp)

```C++
    // C03:08_gotoKeyword.cpp
    // The infamous goto is supported in C++

    #include <iostream>
    using namespace std;

    int main()
    {
        long val;
        for (int i = 0; i < 1000; i++)
        {
            for (int j = 1; j < 100; j += 10)
            {
                val = i * j;
                if(val > 47000)
                    goto bottom;
                    // Break would only go on the outer 'for'
            }
        }
        bottom:
        cout << val << endl;
        return 0;
    }
```

一个可供选择的方法是设置一个布尔值，在外层 `for` 循环对它进行测试，然后利用 `break` 从内层 `for` 循环跳出。

### 3.2.9 递归

递归可以在函数内部，调用函数本身。

> 代码示例：
[09_CatsInHats.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/3.%20The%20C%20in%20C%2B%2B/09_CatsInHats.cpp)

```C++
    // C03:10_CatsInHats.cpp
    // Simple demonstration of recursion

    #include <iostream>
    using namespace std;

    void removeHat(char cat)
    {
        for(char c = 'A'; c < cat; c++)
            cout << " ";
        if(cat <= 'Z'){
            cout << "cat " << cat << endl;
            removeHat(cat+1);
        }
        else
            cout << "VOOM!!!" << endl;
    }

    int main()
    {
        removeHat ('A');
    }
```

在 `removeHat()` 中，只要 `cat` 的值小于'Z'，就会在 `removeHat()` 中调用 `removeHat()`，从而实现递归。每次调用 `removeHat()`，它的参数比当前的 `cat` 值增加1，所以参数不断增加，直到大于'Z'。

## 3.3 运算符简介

我们可以把运算符看做是一种特殊的函数（C++的运算符重载正是以这种方式对待运算符）。一个运算符带一个或更多的参数并产生一个新值。运算符参数和普通的函数调用参数相比在形式上不同，但是作用是一样的。

### 3.3.1 优先级

运算符优先级规定表达式中出现多个不同运算符时计值的运算顺序。

### 3.3.2 自增和自减

自减运算符是`--`，意思是“减小一个单位”。自增运算符是`++`，意思是“增加一个单位”。自增和自减产生一个变量的值作为结果。如果运算符在变量之前出现（即`++A`），**则先执行运算，再产生结果值**。如果运算符在变量之后出现（即`A++`），**则产生当前值，再执行运算**。例如：
> 代码示例：
[10_AutoIncrement.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/3.%20The%20C%20in%20C%2B%2B/10_AutoIncrement.cpp)

```C++
    // C03:10_AutoIncrement.cpp
    // Shows use of auto-increment and auto-decrement operators

    #include <iostream>
    using namespace std;

    int main()
    {
        int i = 0;
        int j = 0;
        cout << "++i-> " << ++i << endl;  // Pre-increment
        cout << "j++-> " << j++ << endl;  // Post-increment
        cout << "--i-> " << --i << endl;   // Pre-decrement
        cout << "j---> " << j-- << endl;   // Post-decrement
        return 0;
    }
```

## 3.4 数据类型简介

在编写程序中，**数据类型**（data type）定义使用存储空间（内存）的方式。通过定义数据类型，告诉编译器怎样创建一片特定的存储空间，以及怎样操纵这片存储空间。

### 3.4.1 基本内部类型

标准C的内部类型（由C++继承）规范不说明每一个内部类型必须有多少位。规范只规定**内部类型必须能存储的最大值和最小值**。

系统头文件 `limits.h` 和 `float.h` 中定义了不同的数据类型可能存储的最大值和最小值（在C++中，一般用 `#include<climits>` 和 `<cfloat>` 代替）。

C和C++中有4个基本的内部数据类型。`char` 存储**字符**，使用最小的8位（一个字节）的存储，尽管它可能占用更大的空间。`Int` 存储**整数值**，使用最小两个字节的存储空间。`float` 和 `double` 类型存储**浮点数**，一般使用IEEE的浮点格式。`float` 用于单精度浮点数，`double` 用于双精度浮点数。

> 代码示例：
[11_Basic.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/3.%20The%20C%20in%20C%2B%2B/11_Basic.cpp)

```C++
    // C03:11_Basic.cpp
    // Defining the four basics data types in C and C++

    int main()
    {
        // Definition without initialization:
        char protein;
        int carbohydrates;
        float fiber;
        double fat;

        // Simultaneous definition & initialization:
        char pizza = 'A', pop = 'Z';
        int dongdings = 100, twinkles = 150,
            heehos = 200;
        float chocolate = 3.14159;
        // Expotential notation
        double fudfe_ripple = 6e-4;
        return 0;
    }
```

程序的第一部分定义了4种基本数据类型的变量，没有对变量初始化。程序的第二部分同时定义和初始化变量（如果可能，最好在定义时提供初始值）。

### 3.4.2 bool类型与true和false

标准C++的`bool`类型有两种由内部的常量`true`（转换为整数1）和`false`（转换为整数0）表示的状态。

### 3.4.3 说明符

**说明符（specifier）用于改变基本内部类型的含义并把它们扩展成一个更大的集合**。有4个说明符：`long`、`short`、`signed`和`unsigned`。

`long`和`short`修改数据类型本身所具有的最大值和最小值。整数类型的大小等级是：`short int`、`int`、`long int`。

浮点数的大小等级是：`float`、`double`和`long double`。`long float`是不合法的类型，也没有`short`浮点数。

`signed`和`unsigned`修饰符告诉编译器**怎样使用整数类型和字符的符号位（浮点数总含有一个符号）**。`unsigned`数不保存符号，因此有一个多余的位可用，所以它能存储比`signed`数大两倍的正数。`signed`是默认的，只有`char`才一定要使用`signed`；`char`可以默认为`signed`，也可以不默认为`signed`。通过规定`signed char`，可以强制使用符号位。

下面的例子使用`sizeof`运算符显示用字节表示的数据类型的大小：
> 代码示例：
[12_Sepcify.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/3.%20The%20C%20in%20C%2B%2B/12_Sepcify.cpp)

```C++
    // C03:12_Specify.cpp
    // Demonstrates the use of specifiers

    #include <iostream>
    using namespace std;

    int main()
    {
        char c;
        unsigned char cu;
        int i;
        unsigned int iu;
        short int is;
        short iis;  // same as short int
        unsigned short int isu;
        unsigned short iisu;
        long int il;
        long iil;   // same as long int
        unsigned long int ilu;
        unsigned long iilu;
        float f;
        double d;
        long double ld;

        cout
            << "\n char= " << sizeof(c)
            << "\n unsigned char= " << sizeof(cu)
            << "\n int= " << sizeof(i)
            << "\n unsigned int= " << sizeof(iu)
            << "\n short = " << sizeof(is)
            << "\n unsigned short= " << sizeof(isu)
            << "\n long = " << sizeof(il)
            << "\n unsigned long= " << sizeof(ilu)
            << "\n float = " << sizeof(f)
            << "\n double = " << sizeof(d)
            << "\n long double = " << sizeof(ld)
            << endl;
        return 0;
    }
```

其中，当用`short`或`long`改变`int`时，关键字`int`是可选的。

### 3.4.4 指针简介

程序中的所有元素都驻留在内存的某处。内存一般被布置成一系列连续的内存位置；我们通常把这些位置看做是**8位字节**，但实际上每一个空间的大小取决于具体机器的结构，一般称为机器的**字长（word size）**。每一个空间可按它的地址与其他空间区分。

因为程序运行时驻留内存中，所以程序中的每一个元素都有地址。程序运行的时候，程序中的每一个元素在内存中都占有一个位置。甚至函数也占用内存。
> 代码示例：
[13_YourPets1.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/3.%20The%20C%20in%20C%2B%2B/13_YourPets1.cpp)

```C++
    // C03: 13_YourPets1.cpp

    #include <iostream>
    using namespace std;

    int dog, cat, bird, fish;

    void f(int pet)
    {
        cout << "pet id number: " << pet << endl;
    }

    int main()
    {
        int i, j, k;
        return 0;
    }
```

`&`：取址运算符，可获得标识符的地址。
> 代码示例：
[14_YourPets2.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/3.%20The%20C%20in%20C%2B%2B/14_YourPets2.cpp)

```C++
// C03: 14_YourPets2.cpp

#include <iostream>
using namespace std;

int dog, cat, bird, fish;

void f(int pet)
{
    cout << "pet id number: " << pet << endl;
}

int main()
{
    int i, j, k;

    cout << "f(): " << (long) &f << endl;
    cout << "dog: " << (long) &dog << endl;
    cout << "cat: " << (long) &cat << endl;
    cout << "bird: " << (long) &bird << endl;
    cout << "fish: " << (long) &fish << endl;
    cout << "i: " << (long) &i << endl;
    cout << "j: " << (long) &j << endl;
    cout << "k: " << (long) &k << endl;
    return 0;
}
```

`(long)` 是一种**类型转换（cast）**。在此处不是必须的。

C和C++中专门存放地址的变量类型叫做**指针(pointer)**。定义指针的运算符为`*`。定义指针时，必须规定它指向的变量类型。如一个指向`int`的指针：`int* ip`。同时，C++编程的一般原则是**在定义指针时进行初始化**。

```C++
    int a = 47;
    int *ipa = &a;
```

上述中，已经初始化了整型变量`a`和整型指针`ipa`，`ipa`存放了`a`的地址。指针常用的两大用途：

1. 为了能在函数内改变“外部对象”。
2. 为了获取更多灵活的编程技巧。

### 3.4.5 修改外部对象

通常，向函数传递参数时，在函数内部生成该参数的一个拷贝。这称为**按值传递(pass-by-value)**。在下面的程序中能看到按值传递的效果：

> 代码示例：
[15_PassByValue.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/3.%20The%20C%20in%20C%2B%2B/15_PassByValue.cpp)

```C++
    // C03: 15_PassByValue.cpp

    #include <iostream>
    using namespace std;

    void f(int a)
    {
        cout << "a= " << a << endl;
        a = 5;
        cout << "a= " << a << endl;
    }

    int main()
    {
        int x = 47;
        cout << "x= " << x << endl;
        f(x);
        cout << "x= " << x << endl;
        return 0;
    }
```

```C++
    输出结果：
    x= 47
    a= 47
    a= 5
    x= 47
```

在函数`f()`中，`a`是一个局部变量（local variable），它只有在调用函数`f()`期间存在。因为它是一个函数参数，所以调用函数时通过参数传递来初始化a的值；在main函数中参数是x，其值为47，所以当调用函数`f()`时，这个值被拷贝到a中。

当在函数`f()`内部时，变量x就是外部对象（outside object）。显然，改变局部变量并不会影响外部变量，因为它们分别放在存储空间的不同位置。但是，如果我们的确想修改外部对象那又该怎么办呢？这时指针就该派上用场了。在某种意义上，**指针是另一个变量的别名**。所以如果我们不是传递一个普通的值而是传递一个指针给函数，实际上就是传递外部对象的别名，使函数能修改外部对象，如像：
> 代码示例：
[16_PassAddress.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/3.%20The%20C%20in%20C%2B%2B/16_PassAddress.cpp)

```C++
    // C03:16_PassAddress.cpp

    #include <iostream>
    using namespace std;

    void f(int* p)
    {
        cout << "p = " << p << endl;
        cout << "*p = " << *p << endl;
        *p = 5;
        cout << "p = " << p << endl;
    }

    int main()
    {
        int x = 47;
        cout << "x = " << x << endl;
        cout << "&x = " << &x << endl;
        f(&x);
        cout << "x = " << x << endl;
        return 0;
    }
```

```C++
    输出结果：
    x = 47
    &x = 0x61fe1c
    p = 0x61fe1c
    *p = 47
    p = 0x61fe1c
    x = 5
```

现在函数`f()`把指针作为参数，并且在赋值期间间接引用这个指针，这就使得外部对象`x`被修改。`p`中的值就是变量`x`的地址，指针`p`的确是指向变量`x`。当改变指针`p`指向的变量值并间接引用赋值为5，我们看到变量`x`的值现在已经改变为5了。

### 3.4.6 C++引用简介

**引用传递（pass-by-reference）**：用引用传递参数地址。

> 代码示例：
[17_PassReference.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/3.%20The%20C%20in%20C%2B%2B/17_PassReference.cpp)

```C++
    // C03:17_PassReference.cpp

    #include <iostream>
    using namespace std;

    void f(int& r)
    {
        cout << "r = " << r << endl;
        cout << "&r = " << &r << endl;
        r = 5;
        cout << "r = " << r << endl;
    }

    int main()
    {
        int x = 47;
        cout << "x = " << x << endl;
        cout << "&x = " << &x << endl;
        f(x);
        cout << "x = " << x << endl;
        return 0;
    }
```

```C++
    x = 47
    &x = 0x61fe1c
    r = 47
    &r = 0x61fe1c
    r = 5
    x = 5
```

以引用传递允许一个函数去修改外部对象，就像传递一个指针所做的那样。

### 3.4.7 用指针和引用作为修饰符

将基本的数据类型`char`、`int`、`float`和`double`，与修饰符`signed`、`unsigned`、`short`和`long`，以及指针和引用（它们与基本数据类型和修饰符是独立的），可以产生三倍的结合：
> 代码示例：
[18_AllDefinitions.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/3.%20The%20C%20in%20C%2B%2B/18_AllDefinitions.cpp)

```C++
    //：C03：A11Definitions.cpp
    //A11possible combinations of basic data types，specifiers，pointers and references.
    #include<iostream>
    using namespace std;

    void fl(char c, int i, float f, double d);
    void f2(short int si,long int li,long double ld);
    void f3(unsigned char uc, unsigned int ui, unsigned short int usi, unsigned long int uli);
    void f4(char*cp, int*ip, float*fp, double*dp);
    void f5(short int*sip, long int*lip, long double*ldp);
    void f6(unsigned char*ucp,unsigned int*uip, unsigned short int*usip, unsigned long int* ulip);
    void f7(char& cr, int& ir, float& fr, double&dr);
    void f8(short int& sir, long int& lir, long double& ldr);
    void f9(unsigned char& ucr, unsigned int& uir, unsigned short int& usir, unsigned long int& ulir);
    int main()
    {}
```

这里有和指针一起工作的另一种类型：`void`。如果声明指针是`void*`，它意味着任何类型的地址都可以间接引用那个指针（而如果声明`int*`，则只能对`int`型变量的地址间接引用那个指针）。
> 代码示例：
[19_VoidPointer.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/3.%20The%20C%20in%20C%2B%2B/19_VoidPointer.cpp)

```C++
    // C03:19_VoidPointer.cpp

    #include <iostream>
    using namespace std;
    int main()
    {
        void* vp;
        char c;
        int i;
        float f;
        double d;
        // The address of ANY type can be assigned to a void pointer:
        vp = &c;
        vp = &i;
        vp = &f;
        vp = &d;
    }
```

一旦简介引用一个`void*`，就会丢失关于类型的信息。这意味着在使用前，必须转换为正确的类型：
> 代码示例：
[20_CasrFromVoidPointer.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/3.%20The%20C%20in%20C%2B%2B/20_CasrFromVoidPointer.cpp)

```C++
    // C03:20_CasrFromVoidPointer.cpp

    int main()
    {
        int i = 99;
        void* vp = &i;
        // Can't dereference(解除引用) a void pointer:
        // *vp = 3; // compile-time error
        // Must cast back to int before dereferencing:
        *((int*)vp) = 3;
        return 0;
    }
```

转换`(int*)vp`告诉编译器把`void*`当作`int*`处理，因此可以成功地对它间接引用。同时也有可能将`int*`转换为一个`char*`或`double*`，这将改变已经分配给`int`的存储空间大小，可能会引起程序崩溃。因此应当避免使用`void`指针。

## 3.5 作用域

作用域规则告诉我们一个变量的有效范围，它在哪里创建，在哪里销毁。**变量的有效作用域从它的定义点开始，到和定义变量之前最邻近的开括号配对的第一个闭括号**。也就是说，作用域由变量所在的最近一对括号确定。说明如下：
> 代码示例：
[21_Scope.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/3.%20The%20C%20in%20C%2B%2B/21_Scope.cpp)

```C++
    // C03：Scope.cpp
    //How variables are scoped
    using namespace std;

    int main()
    {
        int scpl;
        //scpl visible here
        {
            //scpl still visible here
            // ......
            int scp2;
            //scp2 visible here
            // ......
            {
                //scp1&scp2 still visible here
                // .....
                int scp3;
                //scp1，scp2 & scp3 visible here
                // ......
            }//<--scp3 destroyed here
            // scp3 not available here
            // scpl & scp2 still visible here
            //......
        } //<--scp2 destroyed here
        // scp3 & scp2 not available here
        //scp1 still visible here
        // ......
    }  //<--scp1 destroyed here
```

上面的例子表明什么时候变量是可见的，什么时候变量是不可用的（即变量越出其作用域）。只有在变量的作用域内，才能使用它。作用域可以嵌套，即在一对大括号里面有其他的大括号对。嵌套意味着可以在我们所处的作用域内访问外层作用域的一个变量。上面的例子中，变量scp1在所有的作用域内都可用，而scp3只能在最里面的作用域内才可用。

### 3.5.1 实时定义变量

读C代码时， 进入一个作用域， 首先看到的是一个变量的定义块，在块的开始部分声明所
有的变量。C+＋(不是C)允许在作用域内的任意地方定义变量， 所以可以在正好使用它之前定义。
> 代码示例：
[22_OnTheFly.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/3.%20The%20C%20in%20C%2B%2B/22_OnTheFly.cpp)

```C++
    // C03:22_OnTheFly.cpp
    // On-the-fly variable definitions

    #include <iostream>
    using namespace std;

    int main()
    {
        {   // Begin a new scope
            int q = 0;  // C requires definitions here
            // ...
            // Define at point of use:
            for(int i = 0; i < 100; ++i){
                q++;    // q comes from a larger scope
                // Definition at the end of the scope:
                int p = 12;
            }
            int p = 1;  // A different p
        }   // End scope containing q & outer p
        cout << "Tpe characters:" << endl;
        while(char c = cin.get() != 'q'){
            cout << c << " wasn't it" << endl;
            if(char x = c == 'a' || c == 'b')
                cout << "You typed a or b" << endl;
            else
                cout << "You typed " << x << endl;
        }
        cout << "Type A, B, or C" << endl;
        switch(int i = cin.get()){
            case 'A': cout << "snap" << endl; break;
            case 'B': cout << "Crackle" << endl; break;
            case 'C': cout << "Pop" << endl; break;
            default: cout << "Not A, B or C!" << endl;
        }
    }
```

尽管例子表明在`while`语句、`if`语句和`switch`语句中也可以定义变量， 但是可能因为语法受到许多限制， 这种定义不如在`for`的表达式中常用。例如，**我们不能有任何插入括号**。也比可以写出：

```C++
    while((char c = cin.get()) != 'q')
```

附加的括号似乎是合理的，但因为无法使用括号，结果就不像所希望的那样。同时，因为 `！=` 比 `=` 的优先级高， 所以`char c`最终含有的值是由`bool`转换为`char`的。

## 3.6 指定存储空间分配

### 3.6.1 全局变量

全局变量是在所有函数体的外部定义的， 程序的所有部分（甚至其他文件中的代码）都
可以使用。如果在一个文件中使用`extern`关键字来声明**另一个文件中存在的全局变量**， 那么这个文件可以使用这个数据。
> 代码示例：
[23_Global.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/3.%20The%20C%20in%20C%2B%2B/23_Global.cpp)

```C++
    // C03:23_Global.cpp
    // Demonstration of global variables

    #include <iostream>
    using namespace std;

    int globe;
    void func();
    int main()
    {
        globe = 12;
        cout << globe << endl;
        func(); //Modifies globe
        cout << globe << endl;
    }
```

```C++
    // C03: 23_Global2.cpp
    // Accessing external global variables
    extern int globe;
    void func()
    {
        globe = 47;
    }
```

变量`globe`的存储空间是在程序Global.cpp中定义创建的，在Global2.cpp的代码中可以
访问同一个变量。由于Global2.cpp和Global.cpp的代码是分段编译的，必须通过声明：`extern int globe`告诉编译器变量存在哪里。运行这个程序时，会看到函数`func()`的调用的确影响`globe`的全局实例。
> 备注vecode编译未通过

### 3.6.2 静态变量

静态变量（static）初始化只在函数第一次调用时执行，函数调用之间变益的值保持不变。static变址的优点是**在函数范围之外它是不可用的**。
> 代码示例：
[24_Static.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/3.%20The%20C%20in%20C%2B%2B/24_Static.cpp)

```C++
    // C03:24_Static.cpp
    // Using a static variable in a function

    #include <iostream>
    using namespace std;

    void func()
    {
        static int i = 0;
        cout << "i = " << ++i << endl;
    }

    int main()
    {
        for(int x = 0; x < 10; ++x)
            func();
        return 0;
    }
```

每一次在`for`循环中调用函数`func()`时，它都打印不同的值（在本示例中输出1~10）。如果不使用关键字`static`, 打印出的值总是'1'。

`static`的第二层意思是：“在某个作用域外不可访问”。当应用`static`于函数名和所有函数外部的变量时， 它的意思是“在文件的外部不可以使用这个名字”。函数名或变量是局部于文件的；我们说它具有**文件作用域(file scope)**。
> 代码示例：
[25_FileStatic.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/3.%20The%20C%20in%20C%2B%2B/25_FileStatic.cpp)

```C++
    // C03:25_FileStatic.cpp
    // File scope demonstration. Compiling and linking this file with
    // 25_FileStatic2.cpp will cause a linker error.

    // File scope means only available in this file:
    static int fs;

    int main()
    {
        fs = 1;
    }
```

尽管在下面的文件中变量`fs`被声明为`extern`，但是连接器不会找到它，因为在FileStatic.cpp中它被声明为`static`。

```C++
    // C03: 25_FileStatic2.cpp
    // Trying to reference fs

    extern int fs;
    void func()
    {
        fs = 100;
    }
```

### 3.6.4 外部变量

`extern`关键字，告诉编译器存在着一个变量和函数， 即使编译器在当前编译的文件中没有看到它，但这个变量或函数可能在另一个文件中或者在当前文件的后面定义。
> 代码示例：
[26_Forward.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/3.%20The%20C%20in%20C%2B%2B/26_Forward.cpp)

```C++
    // C03: 26_Forward.cpp
    // Forward function & data declarations

    #include <iostream>
    using namespace std;

    // This is not actually external, but the compiler must be told it exists somewhere
    extern int i;
    extern void func();

    int main()
    {
        i = 0;
        func();
    }

    int i;  // The data Definition
    void func()
    {
        i++;
        cout << i;
    }
```

当编译器遇到`extern int i`时， 它知道`i`肯定作为全局变量存在于某处。当编译器看到变量`i`的定义时，并没有看到别的声明；所以知道它在文件的前面已经找到了同样声明的`i`。如果已经把变量`i`定义为`static`,又要告诉编译器，`i`是全局定义的(通过`extern`)，但是，它也有文件作用域(通过`static`)，所以编译器会产生错误。

#### 3.6.4.1 连接

在一个执行程序中，标识符代表存放变量或被编译过的函数体的存储空间。**连接(linkage)**用连接器所见的方式描述存储空间。连接方式有两种：**内部连接( internal linkage)**和**外部连接(external linkage)**。

内部连接意味着只对正被编译的文件创建存储空间。用内部连接，别的文件可以使用相同的标识符或全局变量，连接器不会发现冲突——也就是为每一个标识符创建单独的存储空间。在C和C++中，内部连接是由关键字`static`指定的。

外部连接意味着为所有被编译过的文件创建一片单独的存储空间。一且创建存储空间，连接器必须解决所有对这片存储空间的引用。全局变量和函数名有外部连接。通过用关键字
`extern`声明， 可以从其他文件访问这些变量和函数。

### 3.6.5 常量

修饰符`const`告诉编译器这个名字表示常量。在C++中，一个`const`必须有初始值。常量值前带0被认为是八进制数(基数为8)。常量值前带0x被认为是十六进制数（基数为16)。对于浮点数，我们可以对数加后缀强加浮点数类型：f或F强加`float`型，L或l强加`long double`型，否则是`double`型。

字符常址是用**单引号**括起来的字符，如`'A'`、`'0'`。注意字符`'0'`(ASCII 96)和数值0之间存在巨大差别。

### 3.6.6 volatile常量

限定词`const`告诉编译器“这是不会改变的”（这就允许编译器执行额外的优化）；而限定
词`volatile`则告诉编译器“不知道何时会改变”，防止编译器依据变量的稳定性作任何优化。

## 3.7 运算符及其使用

除了赋值、自增、自减运算符之外，运算符所产生的值不会修改操作数。修改操作数被称为**副作用(side effect)**。

### 3.7.1 赋值

赋值操作由运算符`=`实现。这意味着“取右边的值[通常称之为右值(rvalue)]井把它拷贝给左边[通常称之为左值([value)]”。右值可以是任意常量、变量或能产生值的表达式，但是左值必须是一个明确命名的变量（也就是说，应该有一个存储数据的物理空间）。例如，可以给一个变量赋值常量`A = 4;`，但是不能给常量赋任何值，因为它不能是左值。

### 3.7.2 数学运算符

加(+)、减(-)、乘(*)、除(/)、取模(%)。
> 代码示例：
[27_Mathops.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/3.%20The%20C%20in%20C%2B%2B/27_Mathops.cpp)

```C++
    // C03: Mathops.cpp
    // Mathematical operators
    #include <iostream>
    using namespace std;

    // A macro to display a string and a value.
    #define PRINT(STR, VAR) cout << STR << " = " << VAR << endl

    int main()
    {
        int i, j, k;
        float u, v, w;  // Applies to doubles, too
        cout << "Enter an integer: ";
        cin >> j;
        cout << "Enter another integer: ";
        cin >> k;
        PRINT("j", j); PRINT("k", k);
        i = j + k; PRINT("j + k", i);
        i = j - k; PRINT("j - k", i);
        i = j / k; PRINT("j / k", i);
        i = j * k; PRINT("j * k", i);
        i = k % j; PRINT("k % j", i);

        // The following only works with integers
        j %= k; PRINT("j %= k", j);

        cout << "Enter a floating-point number: ";
        cin >> v;
        cout << "Enter another floating-point number: ";
        cin >> w;
        PRINT("v", v); PRINT("w", w);
        u = v + w; PRINT("v + w", u);
        u = v - w; PRINT("v - w", u);
        u = v * w; PRINT("v * w", u);
        u = v / w; PRINT("v / w", u);

        // The following works for ints, chars and doubles too:
        PRINT("u", u); PRINT("v", v);
        u += v; PRINT("u += v", u);
        u -= v; PRINT("u -= v", u);
        u *= v; PRINT("u *= v", u);
        u /= v; PRINT("u /= v", u);
    }
```

#### 3.7.2.1 预处理宏介绍

使用宏`PRINT()`可以节省输入(和避免输入错误！)。传统上用**大写字母**来命名预处理宏以便突出它。跟在宏名后面的括号中的参数会被闭括号后面的所有代码替代。只要在调用宏的地方，预处理程序就删除名字`PRINT`并替换代码，所以使用宏名时编译器不会报告任何错误信息，**它并不对参数做任何类型检查**。

### 3.7.3 关系运算符

关系运算符在操作数之间建立一种关系。如果关系为真，则产生bool值`true`；如果关系为假，则产生bool值`false`。关系运算符有：小于(`<`)，大于(`>`)，小于等于(`<=`)，大于等于(`>=`)，恒等于(`==`)，不等于(`!=`)。

### 3.7.4 逻辑运算符

逻辑运算符“与”(`&&`）和“或”(`||`)依据它们的参数的逻辑关系产生`true`或`false`。在C++中，如果语句是非零值，则为`true`，如果是零值则为`false`。
> 代码示例：
[28_Boolean.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/3.%20The%20C%20in%20C%2B%2B/28_Boolean.cpp)

```C++
    // C03:28_Boolean.cpp
    // Relationship and operators

    #include <iostream>
    using namespace std;

    int main()
    {
        int i, j;
        cout << "Enter an integer: ";
        cin >> i;
        cout << "Enter another integer: ";
        cin >> j;
        cout << "i > j is " << (i > j) << endl;
        cout << "i < j is " << (i < j) << endl;
        cout << "i >= j is " << (i >= j) << endl;
        cout << "i <= j is " << (i <= j) << endl;
        cout << "i == j is " << (i == j) << endl;
        cout << "i != j is " << (i != j) << endl;
        cout << "i && j is " << (i && j) << endl;
        cout << "i || j is " << (i || j) << endl;
        cout << "(i < 10) && (j < 10) is " << ((i < 10) && (j < 10)) << endl;
        return 0;
    }
```

### 3.7.5 位运算符

位运算符允许在一个数中处理个别的位（因为浮点数使用一种特殊的内部格式，所以位运算符只适用于整型char、int和long）。

如果两个输入位都是1, 则 “与” 运算符(`&`)在结果位上产生1, 否则为0。如果两个输入位有一个是1, 则 “或” 运算符(`|`)在结果位上产生1，只有当两个输入位都是0时，结果
位才为0。如果两个输入位之一是1而不是同时为1，则位的 “异或” 运算符xor(`^`)的结果位为1。位的 “非” 运算符(`~`)，也称为补运算是一个一元运算符，它只带一个参数（其他的运算符是二元运算符）。非运算符运算的结果和输入位相反，即输入位为0时结果位为1，输入位为1时结果位为0。

### 3.7.6 移位运算符

移位运算符也是对位的操纵。左移位运算符(`<<`)引起运算符左边的操作数向左移动，移动位数由运算符后面的操作数指定。右移位运算符(`>>`)引起运算符左边的操作数向右移动，移动位数由运算符后面的操作数指定。如果移位运算符后面的值比运算符左边的操作数的位数大，则结果是不定的。如果左边的操作数是无符号的，右移是逻辑移，所以最高位补零。如果左边的操作数是有符号的，右移可能是也可能不是逻辑移位（也就是说，行为是不定的）。
> 代码示例：
[29_BitWise.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/3.%20The%20C%20in%20C%2B%2B/29_BitWise.cpp)

```C++
    // C03: 29_printBinary.h
    // Display a byte in binary

    void printBinary(const unsigned char val);

    // C03: 29_printBinary.cpp
    #include <iostream>
    #include "29_printBinary.h"

    void printBinary(const unsigned char val)
    {
        for(int i = 7; i >= 0; i--)
        {
            if(val & (1 << 7))
                std::cout << "1";
            else
                std::cout << "0";
        }
    }


```

函数`printBinary()`取出一个字节井一位一位地显示出来。表达式`(1 << i)`在每一个相继位的位置产生一个l。如果这一位和变量val按位“与”，并且结果不是零，就表明val的这一位为1。

`<<` 和 `>>` 实现位的移位功能，但是当移位越出数的一端时，那些位就会丢失（这就是通常所说的，那些位掉进了神秘的位桶(bit bucket)中，丢弃在这个桶中的位有可能需要重用）。操作位的时候，也可以执行旋转(rotation)，即在一端移掉的位插入到另一端，好像它们在绕着一个回路旋转。

> 代码示例：
[30_Rotation.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/3.%20The%20C%20in%20C%2B%2B/30_Rotation.cpp)

```C++
    // C03:30_Rotation.cpp
    // Perform left and right rotations

    unsigned char rol(unsigned char val)
    {
        int highbit;
        if(val & 0x80)  // 0x80 is the high bit only
            highbit = 1;
        else
            highbit = 0;
        // left shift (bottom bit becomes 0):
        val <<= 1;
        // Rotate the high bit onto the bottom
        val != highbit;
        return val;
    }

    unsigned char ror(unsigned char val)
    {
        int lowbit;
        if(val & 1) // Check the low bit
            lowbit = 1;
        else
            lowbit = 0;
        val >> 1;   // Right shift by one position
        // Rotate the low bit onto the top:
        val |= (lowbit << 7);
        return val;
    }
```

### 3.7.7 一元运算符

逻辑非(`!`)对一个`true`值得到一个`false`值。地址运算符(`&`)，间接引用(`*`和`->`)和强制类型转换运算符，`new`和`delete`均为一元元素符。

### 3.7.8 三元运算符

`if-else`语句的可表示为`(表达式1) ? (表达式2) : (表达式3)`的形式。如果表达式1的计值位`true`，则执行表达式2（即问号后的表达式），若表达式1的计值为`false`，则执行冒号后的表达式3。

### 3.7.9 逗号运算符

逗号并不只是在定义多个变量时用来分隔变最， 如像`int i, j , k;`当然， 它也用于函数参数列表中。同时，它也可用于分隔表达式。在这种情况下，它只产生最后一个表达式的值。在逗号分隔的列表种，其余的表达式只完成它们的副作用。下面例子自增一串变量，并把最后一个作为右值。
> 代码示例：
[31_CommaOperator.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/3.%20The%20C%20in%20C%2B%2B/31_CommaOperator.cpp)

```C++
    // C03:31_CommaOperator.cpp
    #include <iostream>
    using namespace std;
    int main()
    {
        int a = 0, b = 1, c = 2, d = 3, e = 4;
        a = (b++, c++, d++, e++);
        cout << "a = " << a << endl;
        // The patenthesses are critical here. without them the statement will evaluate to:
        (a = b++), c++, d++, e++;
        cout << "a = " << a << endl;
        return 0;
    }
```

```C++
    输出结果：
    a = 4
    a = 2
```

通常， 除了作为一个分隔符， 逗号最好不作他用。

### 3.7.10 使用运算符时的常见问题

使用运算符时的一个问题是总不愿使用括号，另外一个十分常见的问题如下所示：

```C++
    // C03: Pitfall.cpp
    // Operator mistakes
    int main()
    {
        int a = 1, b = 1;
        while(a = b)
        // ...
    }
```

当b不为零时，语句`a = b`总是为真，而b的值也是由运算符“=”产生的，在条件语句中，应当使用等值运算符“==”。同样的，使用位运算符中的“与”和“或”，而不是它们响应的逻辑运算符。

### 3.7.11 转换运算符

**转换(cast)**，它会自动把一种数据类型转换为另一种类型。为了实现转换，要用括号把所想要转换的数据类型（包括所有的修饰符）括起来放在值的左边。这个值可以是一个变量、一个常量、由一个表达式产生的值或是一个函数的返回值。下面是一个例子：

```C++
    // C03: SimpleCast.cpp
    int main()
    {
        int b = 200;
        unsigned long a = (unsigned long int ) b;
    }
```

C+＋有一个另外的转换语法，它遵从函数调用的语法。这个语法给参数加上括号而不是给数据类型加上括号，类似千函数调用：

```C++
    // C03: FunctionCallCast.cpp
    int main()
    {
        float a = float(200);
        // This is equivalent to:
        float b = (float) 200;
    }
```

当然对于上面的情况，我们实际上不需要转换，只要写200f（实际上，一般编译器会对上面的表达式作转换）。转换一般用于变量，而不用于常量。

### 3.7.12 C++的显示转换

|    转换类型    |描述         |
|    :-------:   |:-------            |
| static_cast |用于“良性”和“适度良性”转换，包括不用强制转换（例如自动类型转换）|
|      const_cast      |对“const”和/或“volatile”进行转换|
|   reinterpret_cast  |转换位完全不同的意思。为了安全使用它，关键必须转回原来的类型。转换成的类型一般只能用于位操作，否则就是为了其他隐秘的目的。这是所有转换中最危险的。|
|      dynamic_cast     |用于类型安全的向下转换|

#### 3.7.12.1 静态转换（static_cast）

`static_cast`全部用于明确定义的变换，包括编译器允许我们所做的不用强制转换的“安全”变换和不太安全但清楚定义的变换。`static_cast`包含的转换类型包括典型的非强制变换、窄化（有信息丢失）变换，使用`void*`的强制变换、隐式类型变换和类层次的静态定位。
> 代码示例：
[32_static_cast.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/3.%20The%20C%20in%20C%2B%2B/32_static_cast.cpp)

```C++
    // C03: 32_static_cast.cpp
    void func(int) {}

    int main()
    {
        int i = 0x7fff; // Max pos value = 32767
        long l;
        float f;
        // (1) Typical castless conversions:
        l = i;
        f = i;
        // Also works:
        l = static_cast<long>(i);
        f = static_cast<float>(i);

        // (2) Narrowing conversions:收缩转换
        i = l;  // May lose digits
        i = f;  // May lose info
        // Says "I know," eliminates warnings:
        i = static_cast<int>(l);
        i = static_cast<int>(f);
        char c = static_cast<char>(i);

        // (3) Forcing a conversion from void* :
        void* vp = &i;
        // Old way products a dangerous conversion:
        float* fp = (float*)vp;
        // The new way is equally dangerous:
        fp = static_cast<float*>(vp);

        // (4) Implicit type conversion, normally performed by the compiler:
        double d = 0.0;
        int x = d;  // Automatic type conversion
        x = static_cast<int>(d);    // More explicit
        func(d);    // Automatic type conversion
        func(static_cast<int>(d)); // More explicit
    }
```

程序的第(1)部分，是C中习惯采用的几种变换，有的有强制转换，有的没有强制转换。
把`int`提升到`long`或`float`不会有间题， 因为后者总是能容纳一个int所包含的值。尽管这是不必要的，但是可以使用`static_cast`来突出这些提升。

第(2)部分显示的是另一种变换方式。在这里可能会丢失数据，因为一个`int`和`long`或`float`不是一样“宽”的；它不能容纳同样大小的数字。因此称为**窄化变换(narrowing conversion)**。

C＋＋中不用转换是不允许从`void*`中赋值的（不像C）。

程序的第(4)部分显示编译器自动执行的几种隐式类型变换。

#### 3.7.12.2 常量转换（const_cast）

如果从`const`转换为非`const`或从`volatile`转换为非`volatile`，可以使用`const_cast`。这是`const_cast`惟一允许的转换；如果进行别的转换就可能要使用单独的表达式或者可能会得到一个编译错误。

```C++
    // C03: const_cast.cpp
    int main()
    {
        const int i = 0;
        int* j = (int*) &i; // Deprecated form
        j = const_cast<int*>(&i);   // Preferred
        // Can't do simultaneous additional casting:
        // ! long* l = const_cast(long*)(&i); //Error
        volatile int k = 0;
        int *u = const_cast<int*>(&k);
    }
```

如果取得了`const`对象的地址，就可以生成一个指向`const`的指针，不用转换是不能将它赋给非`const`指针的。旧形式的转换能实现这样的赋值，但是`const_cast`是适用的。`volatile`也是这样。

#### 3.7.12.3 重解释转换（reinterpret_cast）

这是最不安全的一种转换机制，最有可能出问题。`reinterpret_cast`把对象假想为模式（为了某种隐秘的目的），仿佛它是一个完全不同类型的对象。在使用`reinterpret_cast`做任何事之前，实际上总是需要`reinterpret_cast`回到原来的
类型（或者把变批看做是它原来的类型）。
> 代码示例：
[33_reinterpret_cast.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/3.%20The%20C%20in%20C%2B%2B/33_reinterpret_cast.cpp)

```C++
    // C03:33_reinterpret_cast.cpp
    #include <iostream>
    using namespace std;
    const int sz = 100;

    struct X {int a[sz]; };

    void print(X* x)
    {
        for(int i = 0; i < sz; ++i)
            cout << x->a[i] << ' ';
        cout << endl << "--------------------" << endl;
    }

    int main()
    {
        X x;
        print(&x);
        int *xp = reinterpret_cast<int*>(&x);
        for(int* i = xp; i < xp + sz; ++i)
            *i = 0;
        // Can't use xp as an X* at this point unless you cast it_back:
        print(reinterpret_cast<X*>(xp));
        // In this example, you can also just use the original identifier:
        print(&x);
    }
```

`struct X`只包含一个整型数组，但是当用`X x`在堆栈中创建一个变量时，该结构体中的每一个整型变量的值都没有意义(上述程序中的第一个print()函数输出可见)。为了初始化它们，取得`X`的地址并转换为一个整型指针，该指针然后遍历这个数组置每一个整型元素为0。注意i的上限是如何通过计算sz加xp得到的。编译器知道我们实际上是希望sz的指针位置比xp更大，它替我们做了正确的指针算术运算。

`reinterpret_cast`的思想就是当需要使用的时候，所得到的东西已经不同了，以至于它不能用于类型的原来目的，除非再次把它转换回来。这里，我们在打印调用中转换回`X*`，但是当然，因为我们还有原来的标识符，所以还可以使用它。但是`xp`只有作为`int *`才有用，这真的是对原来的`X`的重新解释。

使用`reinterpret_cast`通常是一种不明智、不方便的编程方式， 但是当必须使用它时， 它是非常有用的。

### 3.7.13 sizeof——独立运算符

`sizeof`可计算有关数据项目所分配的内存大小。
> 代码示例：
[34_sizeof.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/3.%20The%20C%20in%20C%2B%2B/34_sizeof.cpp)

```C++
    // C03:34_sizeof.cpp
    #include <iostream>
    using namespace std;

    int main()
    {
        cout << "sizeof(double) = " << sizeof(double);
        cout << ", sizeof(char) = " << sizeof(char);
        return 0;
    }
```

按照定义，任何`char`(`signed`、`unsigned`或普通的）类型的`sizeof`都是1，不管`char`潜在的存储空间是否实际上是一个字节。

注意`sizeof`是一个运算符， 不是函数。如果把它应用于一个类型，必须要像上面所示的那样使用括号，**但是如果对一个变量使用它，可以不要括号**。

```C++
    int main() {
        int x;
        int i = sizeof x;
    }
```

### 3.7.14 asm关键字

这是一种**转义(escape)机制**，允许在C++程序中写汇编代码。在汇编程序代码中经常可以引用C++的变最，这意味着可以方便地和C++代码通信，且限定汇编代码只是用于必要的高效调整，或使用特殊的处理器指令。编写汇编语言时所必须使用的严格语法是依赖于编译器的，在编译器的文档中可以发现有关语法。

### 3.7.15 显示运算符

这是用于位运算符和逻辑运算符的关键字。

|    关键字    |含义         |
|    :-------:   |:-------            |
| and | `&&`（逻辑与）|
|      or      | `||` （逻辑或）|
|   not  | `!`（逻辑非）|
|      not_eq     | `!=`（逻辑不等）|
|      bitand     | `&`（位与）|
|      and_eq     | `&=`（位与赋值）|
|      bitor     | `|` （位或）|
|      or_eq     | `|=` （位或赋值）|
|      xor     | `^`（位异或）|
|      xor_eq     | `^=`（位异或赋值）|
|      compl     | `~`（补）|

## 3.8 创建复合类型

### 3.8.1 用typedef命名别名

`typedef`的语法是： `typedef 原类型名 别名`。当数据类型稍微有点复杂时， 人们经常使用typedef只是为了少敲几个键：`typedef unsigned long ulong`。现在如果写`ulong`, 则编译器知道意思是`unsigned long`。

但是在一些重要的场合， 编译器必须知道我们正在将名字当做类型处理， 所以`typedef`起了关键作用。`typedef`经常会派上用场的地方是指针类型。如：

```C++
    int* x, y;
```

这实际上生成一个`int*x`和一个`int y`（不是一个`int*`）。也就是说，`*`绑定右边，而不是左边。但是，如果使用一个`typedef`:

```C++
    typedef int* IntPtr;
    IntPtr x, t;
```

则`x`和`y`都是`int*`类型。

### 3.8.2 用struct把变量结合在一起

`struct`（结构）是把一组变最组合成一个构造的一种方式。一且创建了一个`struct`, 就可以生成所建立的新类型变量的许多实例。
> 代码示例：
[35_SimpleStruct.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/3.%20The%20C%20in%20C%2B%2B/35_SimpleStruct.cpp)

```C++
    // C03:35_SimpleStruct.cpp
    struct Structurel{
        char c;
        int i;
        float f;
        double d;
    };

    int main()
    {
        struct Structurel s1, s2;
        s1.c = 'a'; // Select an element using a '.'
        s1.i = 1;
        s1.f = 3.14;
        s1.d = 0.00093;
        s2.c = 'a';
        s2.i = 1;
        s2.f = 3.14;
        s2.d = 0.00093;
    }
```

`struct`的声明必须以**分号**结束。在`main()`中，创建了两个`Structurel`的实例：`s1`和`s2`。它们每一个都有各自独立的c、i、f和d变量。`s1`和`s2`表示了完全独立的变量块。

#### 3.8.2.1 指针和struct

如果有一个指向`struct`对象的指针，可以使用一个不同的运算符`->`来选择对象中的元素。
> 代码示例：
[36_SimpleStruct1.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/3.%20The%20C%20in%20C%2B%2B/36_SimpleStruct1.cpp)

```C++
    // C03: 36_SimpleStruct1.cpp
    // Using pointers to structs
    typedef struct Structre3{
        char c;
        int i;
        float f;
        double d;
    } Structre3;

    int main()
    {
        Structre3 s1, s2;
        Structre3* sp = &s1;
        sp->c = 'a'; // Select an element using a '.'
        sp->i = 1;
        sp->f = 3.14;
        sp->d = 0.00093;
        sp = &s2;      // Point to a different struct object
        sp->c = 'a';
        sp->i = 1;
        sp->f = 3.14;
        sp->d = 0.00093;
    }
```

在`main()`中， `struct`指针`sp`最初指向`s1`, 用`->`选择`s1`中的成员来初始化它们。随后`sp`指向`s2`, 以同样的方式初始化那些变量。

### 3.8.3 用enum提高程序清晰度

枚举数据类型是把名字和数字相联系的一种方式。

```C++
    // C03: Enum.cpp
    // Keeping track of shapes

    enum ShapeType{
        circle,
        square,
        rectangle
    };  // Must end with a semicolon like a struct

    int main()
    {
        ShapeType shape = circle;
        // Activities here...
        // Now do something based on what the shape is:
        switch(shape){
            case circle: /* circle stuff*/ break;
            case square: /* square stuff*/ break;
            case rectangle : /* rectangle stuff*/ break;
        }
    }
```

`shape`是被列举的数据类型`ShapeType`的变裁，可以把它的值和列举的值相比较。因为`shape`实际上只是`int`, 所以它可以具有任何一个`int`拥有的值（包括负数）。也可以把`int`变量和枚举值比较。

#### 3.8.3.1 枚举类型检查

在C++中，类型的概念是基础，对于枚举也是如此。如果有一个`color`枚举类型的实例`a`,在C中，可以写`a++`，但在C++中不能这样写。这是因为枚举的增量运算执行两种类型转换， 其中一个在C++中是合法的，另一个是不合法的。首先，枚举的值隐式地从`color`强制转换为`int`，然后递增该值，再把`int`强制转换回`color`类型。在C++中，这是不允许的，因为color是一个独特的类型， 井不等价于一个`int`。

### 3.8.4 用union节省内存

有时一个程序会使用同一个变量处理不同的数据类型。这时可以创建一个`struct`，其中包含需要存储的所有可能的不同类型，或者可以使用**union（联合）**。

`union`把所有的数据放进一个单独的空间内，它计算出放在`union`中的**最大项**所必需的空间数，并生成`union`的大小。使用`union`可以节省内存。

每当在`union`中放置一个值，这个值总是放在`union`开始的同一个地方，但是只使用必需的空间。因此，我们创建的是一个能容纳任何一个`union`变量的“超变量”。所有的`union`变量地址都是一样的（在类或`struct`中，地址是不同的）。

下面是一个使用`union`的例子。试着去掉不同的元素，看看对`union`的大小有什么影响。注意在`union`中声明某个数据类型的多个实例是没有意义的（除非就是要用不同的名字）。
> 代码示例：
[37_Union.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/3.%20The%20C%20in%20C%2B%2B/37_Union.cpp)

```C++
    // C03:37_Union.cpp
    // The size and simple use of a union
    #include <iostream>
    using namespace std;

    union Packed{   // Declaration similar to a class
        char i;
        short j;
        int k;
        long l;
        float f;
        double d;
        // The union will be the size of double,
        // since that's the largest element
        // Selection ends a union, like a struct
    };

    int main()
    {
        cout << "sizeof(Packed) = " << sizeof(Packed) << endl;
        Packed x;
        x.i = 'c';
        cout << x.i << endl;
        x.d = 3.1415926;
        cout << x.d << endl;

        // 一且进行赋值， 编译器并不关心用联合做什么。
        // 在上面的例子中， 可以对x赋一个浮点值：
        x.f = 2.222;
        // 然后把它作为一个int输出。
        cout << x.j;    // (输出13631)
        cout << x.i;    // (输出?)
        // 结果是无用的信息。
    }
```

### 3.8.5 数组

数组是一种复合类型，因为它们允许在一个单一的标识符下把变量结合在一起，一个接着一个。
> 代码示例：
[38_Arrays.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/3.%20The%20C%20in%20C%2B%2B/38_Arrays.cpp)

```C++
    // C03: 38_Arrays.cpp
    #include <iostream>
    using namespace std;

    int main()
    {
        int a[10];
        for(int i = 0; i < 10; ++i){
            a[i] = i * 10;
            cout << "a[" << i << "] = " << a[i] << endl;
        }
    }
```

访问数组速度很快，但需要注意下标不能越界。同时，数组另一个缺陷在于，必须在编译期定义数组的大小。

可以生成任何类型的数组， 甚至是`struct`类型的：
> 代码示例：
[39_StructArray.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/3.%20The%20C%20in%20C%2B%2B/39_StructArray.cpp)

```C++
    // C03: 39_StructArray.cpp
    // An array of struct

    typedef struct {
        int i, j, k;
    }ThreeDPoint;

    int main()
    {
        ThreeDPoint p[10];
        for(int i = 0; i < 10; i++)
        {
            p[i].i = i + 1;
            p[i].j = i + 2;
            p[i].k = i + 3;
        }
    }
```

注意：`struct`中的标识符`i`如何与`for`循环中的`i`无关。

为了知道数组中的相邻元素之间的距离，可以打印出地址如下：
> 代码示例：
[40_ArrayAddresses.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/3.%20The%20C%20in%20C%2B%2B/40_ArrayAddresses.cpp)

```C++
    // C03: 40_ArrayAddresses.cpp
    #include <iostream>
    using namespace std;

    int main()
    {
        int a[10];
        cout << "sizeof(int) = " << sizeof(int) << endl;
        for(int i = 0; i < 10; ++i)
        {
            cout << "&a[" << i << "] = " << &a[i] << endl;
        }
    }
```

#### 3.8.5.1 指针和数组

数组的标识符不像一般变最的标识符。一方面，数组标识符不是左值，不能给它赋值。
它只是一个进入方括号语法的手段，**当给出数组名而没有方括号时，得到的就是数组的起始地址**：
> 代码示例：
[41_ArrayIdentifier.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/3.%20The%20C%20in%20C%2B%2B/41_ArrayIdentifier.cpp)

```C++
    // C03:41_ArrayIdentifier.cpp
    #include <iostream>
    using namespace std;

    int main()
    {
        int a[10];
        cout << "a = " << a << endl;
        cout << "&a[0] = " << &a[0] << endl;
    }
```

上述运行结果相同(以十六进制形式显示)。

因此可以**把数组标识符看作是数组起始处的只读指针**。尽管不能改变数组标识符指向，但是可以另创建指针，使它在数组中移动。事实上，方括号语法和指针一样工作：

```C++
    int main()
    {
        int a[10];
        int* ip = a;
        for(int i = 0; i < 10; i++)
            ip[i] = i * 10;
    }
```

当想给一个函数传递数组时，命名数组以产生它的起始地址的事实相当重要。如果声明
一个数组为函数参数，实际上真正声明的是一个指针。所以在下面的例子中，`funcl()`和`func2()`有一样的参数表：
> 代码示例：
[42_ArrayArguments.cpp]()

```C++
    // C03: ArrayArguments.cpp
    # include <iostream>
    #include <string>
    using namespace std;

    void func1(int a[], int size)
    {
        for(int i = 0; i < size; ++i)
        {
            a[i] = i * i - i;
        }
    }

    void func2(int* a, int size)
    {
        for(int i = 0; i < size; ++i)
        {
            a[i] = i * i + i;
        }
    }

    void print(int a[], string name, int size)
    {
        for(int i = 0; i < size; ++i)
        {
            cout << name << "[" << i << "] = " << a[i] << endl;
        }
    }

    int main()
    {
        int a[5], b[5];
        // Probably garbage values:
        print(a, "a", 5);
        print(b, "b", 5);
        // Initialize the arrays:
        func1(a, 5);
        func1(b, 5);
        print(a, "a", 5);
        print(b, "b", 5);
        // Notice the arrays are always nodified:
        func2(a, 5);
        func2(b, 5);
        print(a, "a", 5);
        print(b, "b", 5);
    }
```


