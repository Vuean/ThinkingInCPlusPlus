# 第二章 对象的创建和使用

本章介绍一些C++语法和程序构造概念，使用几个C++的类库：输入输出流库，介绍`string`类和`vector`容器。

## 2.1 语言的翻译过程

任何一种计算机语言都要从人们容易理解的形式（源代码）转化为计算机能够理解的形式（机器指令）。通常，翻译器分为两类：**解释器**(*interpreter*)和**编译器**(*compiler*)。

### 2.1.1 解释器

解释器将源代码转化成一些动作（它可由多组机器指令组成）并立即执行这些动作。

具备的有点：

- 较好的交互性；
- 适于快速程序开发（不必要求可执行程序）

### 2.1.2 编译器

编译器直接将源代码转化成汇编语言或机器指令。

### 2.1.3 编译过程

某些语言（特别是C/C++）编译时，首先要对源代码执行预处理。**预处理器**（*preprocessor*）是一个简单的程序，它利用程序员（利用*预处理器指令*）定义好的模式代替源代码中的模式。预处理器指令用来节省输入，增加代码的可读性。

编译一般分两步进行：  
首先。对预处理过的代码进行语法分析。编译器将源代码分解成小的单元并把它们按树形结构组织起来。  
然后，在第一步和第二步之间可能会使用**全局优化器**（*global optimizer*）来生成更短、更快的代码。  
最后，由**代码生成器**（*code generator*）遍历语法分析树，把树的每个节点转化成汇编语言或机器代码。

#### 2.1.3.1 静态类型检查

**类型检查**（*type checking*）是编译器在第一步中完成的。类型检查是检查函数参数是否正确使用，以防止程序设计错误。由于类型检查时在编译阶段而不是程序运行阶段进行的，所以称之为**静态类型检查**（*static type checking*）。

## 2.2 分段编译工具

程序分割的最基本方法是创建命名子程序。在C/C++里子程序被成为**函数**（*function*）。  
当调用函数时，可能需要传给函数一些**参数**（*argument*），当执行完程序后，可得到一个**返回值**（*return value*）。  
程序可由多个文件构成，一个文件中的函数，很可能要访问另一些文件中的函数和数据，因此编译一个文件时，C/C++编译器需要知道另一些文件中函数和数据的名字和基本用法。这一“告知编译器”外部函数和数据的名称及基本用法的过程就是**声明**（*declaration*）。

### 2.2.1 声明与定义

**声明**（*declaration*）是向编译器介绍名字——标识符。而**定义**（*definition*）是为名字分配内存空间——“在这里建立变量/函数”。  

在C/C++中，允许在不同地方声明相同的变量和函数，但只能有一个定义（one-definition rule, 单一定义规则）。

#### 2.2.1.1 函数声明的语法

函数声明即给函数取名、指定函数参数类型和返回值。如下述的`func1()`函数声明，它有两个int类型参数，并返回一个int类型值：

```C++
    int func1(int, int);
```

在函数声明时，可以给参数命名。编译器会忽略这些参数名，例如：

```C++
    int func1(int length, int width);
```

#### 2.2.1.2 一点说明

对于带空参数表的函数，C和C++有很大不同。在C语言中，声明`int func2();`表示“一个可带任意参数（任何数目，任意类型）的函数”。而在C++中，表示“不带参数的函数”。

#### 2.2.1.3 函数的定义

函数定义与函数定义类似，但包含函数体——大括号括起来的语句集。如定义函数体为空的函数`func2()`

```C++
    void func2(int length, int width) { }
```

注意：如果要在函数体中使用参数的话，函数定义中的参数必须有名称。

#### 2.2.1.4 变量声明的语法

函数声明包括函数类型（即返回值类型）、函数名、参数列表和一个分号。为实现说明“这只是一个声明，它的定义在别的地方”，可在变量前加`extern`关键字。

在变量定义前加`extern`关键字表示声明一个变量，但不定义它，如：

```C++
    extern int a;
    extern int func1(int length, int width);
```

> 代码示例：
[01_Declare.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/2.%20Making%20%26%20Using%20Objects/01-Declare.cpp)

**函数声明时参数标识符是可选的，但函数定义时要求要求标识符。**

#### 2.2.1.5 包含头文件

**头文件**是一个含有某个库的外部声明函数和变量的文件。包含头文件需要使用`#include`预处理器命令。`#include`有两种方式来指定文件：尖括号(<>)或双引号("").

(1) 以尖括号指定头文件，如：

```C++
    #include <header>
```

用尖括号来指定文件时，预处理器是以特定的方式来寻找文件，一般是环境中或编译器命令行指定的某种寻找路径。

(2) 以引号指定头文件，如：

```C++
    #include "local.h"
```

用双引号时，预处理器以“定义实现的途径”来寻找文件，通常是从当前目录开始寻找。

#### 2.2.1.6 标准C++ include语句格式

### 2.2.2 连接

连接器把由编译器生成的目标模块（一般是带“.o”或“.obj”扩展名的文件）连接成为操作系统可以加载和执行的程序，它是编译过程的最后阶段。

### 2.2.3 使用库文件

使用库必须：

- 1) 包含库文件；
- 2) 使用库中的函数和变量；
- 3) 把库连接进可执行程序。

## 2.3 编写一个C++程序

第一个程序将用到标准的C++ iostream类，可从文件和标准的输入输出设备中（通常指控制台，也可以重定向到文件和设备）读写数据。

### 2.3.1 使用iostream类

`#include <iostream>`

标准输出的含义就是“发送输出的通用场所”，常指控制台。`iostream`包自动定义一个名为`cout`的变量（对象），它接收所有与标准输出半丁的数据。

将数据发送到标准输出，需要操作符`<<`。例如：

```C++
    cout << "howdy!";
```

意思是把字符串“howdy!”发送到`cout`对象（`cout`是“控制台输出（console output）”的简写）。

### 2.3.2 名字空间

`namespace`关键字。库或程序中的每一个C++定义集被封装在一个命名空间中，如果其他的定义有相同的而名字，但它们在不同的命名空间，就不会产生冲突。

### 2.3.3 程序的基本结构

C/C++程序是变量、函数定义、函数调用的集合。

### 2.3.4 “Hello, World!”

> 代码示例：
[02_Hello.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/2.%20Making%20%26%20Using%20Objects/02_Hello.cpp)

```C++
    // C02-02: Hello.cpp

    #include <iostream>
    using namespace std;

    int main()
    {
        cout << "Hello, World! I am "
             << 8 << " Today!" << endl;
    }
```

### 2.3.5 运行编译器

可使用GNU C++编译器。

## 2.4 关于输入输出流

> 代码示例：
[03_Stream2.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/2.%20Making%20%26%20Using%20Objects/03_Stream2.cpp)

```C++
    // C02: Stream2.cpp
    // More streams features
    #include <iostream>
    using namespace std;

    int main()
    {
        // 用操作器指定格式
        cout << "a number in decimal: "
            << dec << 15 << endl;
        cout << "a number in octal: "
            << oct << 15 << endl;
        cout << "a number in hex: "
            << hex << 15 << endl;
        cout << "a floating-point number: "
            << 3.1415926 << endl;
        cout << "non-printing char (escape): "
            << char(27) << endl;
        return 0;
    }
```

上述例子中，输入输出流利用iostream操作符、将数字分别以十进制、八进制和十六进制打印出来（**操作符不进行打印操作，但它给便输出流的状态**）。浮点数的格式由编译器自动确定。此外，通过（显示）**类型转换(cast)**，任何字符都能转换成`char`类型（`char`是保存单字符的数据类型），发送到数据流。

### 2.4.1 字符数组的拼接

C预处理器的一个重要功能就是可以进行**字符数组的拼接**(character array concatenation)。如果两个**加引号**的字符数组邻接，并且它们之间没有标点，编译器就会把这些字符数组连接成单个字符数组。如：

> 代码示例：
[04_Concat.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/2.%20Making%20%26%20Using%20Objects/04_Concat.cpp)

```C++
    // C02: Concat.cpp
    // 字符数组拼接

    #include <iostream>
    using namespace std;

    int main()
    {
        cout << "This is for too long to put on a "
            "single line but it can be broken up with "
            "no ill effects\nas long as three is no "
            "punctuation separating adjacent character "
            "arrays.\n";
        return 0;
    }
```

### 2.4.2 读取输入数据

输入输出流提供了读取输入的功能，用来完成标准输入功能的对象是`cin`（"console input"，控制台输入）。和`cin`一起使用的是输入输出流操作符是`>>`，其可接收**与参数类型相同的输入**。如：

> 代码示例：
[05_Numconv.cpp]()

```C++
    
```