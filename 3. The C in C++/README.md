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
[05_Charlist.cpp]()

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
[06_Menu.cpp]()

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

