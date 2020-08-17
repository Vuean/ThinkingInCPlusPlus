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
[05_Numconv.cpp[](](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/2.%20Making%20%26%20Using%20Objects/05_Numconv.cpp))

```C++
    // C02: Numconv.cpp
    // 将十进制转换为八进制和十六进制

    #include <iostream>
    using namespace std;

    int main()
    {
        int number;
        cout << "Enter a decimal number: ";
        cin >> number;

        cout << "value in octal = 0"
            << oct << number << endl;
        cout << "value in hex = 0x"
            << hex << number << endl;

        return 0;
    }
```

### 2.5 字符串简介

为使用`string`类，需要包含C++头文件`<string>`。`string`类在命名空间std中，因此需要`using`指令。

> 代码示例：
[06_HelloStrings.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/2.%20Making%20%26%20Using%20Objects/06_HelloStrings.cpp)

```C++
    // C02: HelloStrings.cpp
    // The basics of the Standard C++ string class

    #include <string>
    #include <iostream>
    using namespace std;

    int main()
    {
        string s1, s2;  // Empty strings
        string s3 = "hello world!";  // Initialized
        string s4("I am");// Initialized
        s2 = "Today";   // assigning to a string
        s1 = s3 + " " + s4; //combinging strings
        s1 += " tense ";
        cout << s1 + s2 + "!" << endl;
        return 0;
    }
```

字符串 s1 和 s2 初始时刻是空的。s3 和 s4 的两种不同初始化方法效果是相同的。向 `string` 对象赋值可用 `=`；连接 `string` 对象用 `+` 操作符。

## 2.6 文件的读写

为进行文件读写操作，必须包含 `<fstream>` 头文件。为了**读**而打开文件，要创建一个 `ifstream` 对象，用法同 `cin`；为了**写**而打开文件，要创建一个 `ofstream` 对象，用法同 `cout`。

`getline()` 函数：用来把文件中一行读入到 `string` 对象中。其第一个参数是 `ifstream` 对象，从中读取内容；第二个参数是 `stream` 对象。如：

> 代码示例：
[07_Scopy.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/2.%20Making%20%26%20Using%20Objects/07_Scopy.cpp)

```C++
    // C02: Scopy.cpp
    // Copy one fule to another, a line at a time

    #include <fstream>
    #include <iostream>
    #include <string>
    using namespace std;

    int main()
    {
        ifstream in("07_Scopy.cpp");   // Open for reading
        ofstream out("07_Scopy2.cpp");  // Open for writing
        string s;
        while (getline(in, s))
            out << s << "\n";

        return 0;
    }
```

从上面可以看书，为了打开一个文件，只需要将欲建立的文件名交给 `ifstream` 和 `ofstream` 对象即可。

`getline()` 逐行读取字符，遇到换行符终止。`getline()` 将丢弃换行符而不把它存入string对象。因此，想使拷贝的文件看上去和源文件一样，必须加上换行符。

将整个文件拷贝成单独的一个 `string` 对象：

> 代码示例：
[08_FillString.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/2.%20Making%20%26%20Using%20Objects/08_FillString.cpp)

```C++
    // C02: FillString.cpp
    // Read an entire file into a single string

    #include <string>
    #include <iostream>
    #include <fstream>
    using namespace std;

    int main()
    {
        ifstream in("08_FillString.cpp");
        string s, line;
        while (getline(in, line))
        {
            s += line + "\n";
        }
        cout << s;
        return 0;
    }
```

`string` 具有动态特性，不必担心 `string` 的内存分配。

## 2.7 vector简介

`vector` 类是一个**模板(twmplate)**，可有效地用于不同的类型。为了使用`vector` 类，需要包含头文件 `<vector>`：

> 代码示例：
[09_ FillVector.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/2.%20Making%20%26%20Using%20Objects/09_FillVector.cpp)

```C++
    // C02: FillVector.cpp
    // Copy an entire file into a vector of string

    #include <string>
    #include <iostream>
    #include <fstream>
    #include <vector>
    using namespace std;

    int main()
    {
        vector<string> v;
        ifstream in("09_FillVector.cpp");
        string line;
        while(getline(in, line))
            v.push_back(line);  // Add the line to the end
        for (int i = 0; i < v.size(); i++)
        {
            cout << i << ": " << v[i] << endl;
        }
        return 0;
    }
```

修改上述程序，使之把输入分解成由空格分隔的单词而不是一些行。如：

> 代码示例：
[10_GetWords.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/2.%20Making%20%26%20Using%20Objects/10_GetWords.cpp)

```C++
    // C02: GetWords.cpp
    // Break a file into whitespace-separated words

    #include <string>
    #include <iostream>
    #include <fstream>
    #include <vector>
    using namespace std;

    int main()
    {
        vector<string> words;
        ifstream in("10_GetWords.cpp");
        string word;
        while(in >> word)
            words.push_back(word);
        for (int i = 0; i < words.size(); i++)
        {
            cout << words[i] << endl;
        }
        return 0;
    }
```

其中，`while(in >> word)` 表示每次取输入的一个单词，当表达式的值为false时，就意味着文件读完了。

`vector<int>` 示例：
[11_IntVector.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/2.%20Making%20%26%20Using%20Objects/11_IntVector.cpp)

```C++
    // C02: IntVector.cpp
    // Creating a vector that holds integers

    #include <iostream>
    #include <vector>
    using namespace std;

    int main()
    {
        vector<int> v;
        for(int i = 0; i < 10; i++)
            v.push_back(i);

        for (int i = 0; i < v.size(); i++)
        {
            cout << v[i] << ", ";
        }
        cout << endl;

        for (int i = 0; i < v.size(); i++)
        {
            v[i] = v[i] * 10;
        }

        for (int i = 0; i < v.size(); i++)
        {
            cout << v[i] << ", ";
        }
        cout << endl;
        return 0;
    }
```

## 2.8 小结

## 2.9 练习

2-1 修改**Hello.cpp**，使它能打印你的名字和年龄（或者你的鞋码、爱犬的年龄等）。编译并运行修改后的程序。
> [ex1.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/2.%20Making%20%26%20Using%20Objects/Exercise/ex1.cpp)

2-2 以**Stream.cpp**、**Numconv.cpp**为例，编写一个程序，让它根据输入的半径值求出圆面积，并打印。
> [ex2.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/2.%20Making%20%26%20Using%20Objects/Exercise/ex2.cpp)

2-3 编写一个程序用来打开文件并统计文件中以空格隔开的单词数目。
> [ex3.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/2.%20Making%20%26%20Using%20Objects/Exercise/ex3.cpp)

2-4 编写一个程序统计文件中特定单词的出现次数（要求使用string类的运算符“==”来查找单词）。
> [ex4.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/2.%20Making%20%26%20Using%20Objects/Exercise/ex4.cpp)

2-5 修改**FillVector.cpp**使它能够从后向前打印各行。
> [ex5.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/2.%20Making%20%26%20Using%20Objects/Exercise/ex5.cpp)

2-6 修改**FillVector.cpp**使它能把**vector**中的所有元素连接成单独的一个字符串，并打印，但不加上行号。
> [ex6.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/2.%20Making%20%26%20Using%20Objects/Exercise/ex6.cpp)

2-7 编写一个程序，一次显示文件的一行，然后，等待用户按回车键后显示下一行。
> [ex7.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/2.%20Making%20%26%20Using%20Objects/Exercise/ex7.cpp)

2-8 创建一个**vector<float>**，并用一个**for**循环语句向它输入25各浮点数，显示**vector**的结果。
> [ex8.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/2.%20Making%20%26%20Using%20Objects/Exercise/ex8.cpp)

2-9 创建三个**vector<float>**对象，与第8题一样填写前两个对象。编一个**for**循环，把前两个**vector**的每一个相应元素相加起来，结果放入第三个**vector**的相应元素中。显示这三个**vector**的结果。
> [ex9.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/2.%20Making%20%26%20Using%20Objects/Exercise/ex9.cpp)

2-10 编写一个程序，创建一个**vector<float>**，想前面的练习那样输入25个数。求每个数的平方，并把它们放入vector的同样位置。显示运算前后的**vector**。
> [ex10.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/2.%20Making%20%26%20Using%20Objects/Exercise/ex10.cpp)
