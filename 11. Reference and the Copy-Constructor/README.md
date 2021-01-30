# 第11章 引用和拷贝构造函数

在C++中，引用是支持运算符重载语法的基础（见第12章），也为函数参数的传入和传出控制提供了便利。

本章首先简单地介绍一下C和C++的指针的差异，然后介绍引用。但本章的大部分内容将研究对于C++新手来说比较含混的问题：拷贝**构造函数**(**copy-cpnstructor**)。它是一种特殊的构造函数，需要用引用来实现从现有的相同类型的对象中产生新的对象。编译器使用拷贝构造函数通过**按值传递**(**by value**)的方式在函数中传递和返回对象。

本章最后将阐述有点难以理解的C++的**成员指针**(**pointer-to-member**)这个概念。

## 11.1 C++中的指针

C和C++指针的最重要的区别在于C++是一种类型要求更强的语言。C不允许随便地把一个类型的指针赋值给另一个类型，但允许通过`void*`来实现。C++不允许这样做，如果真想把某种类型当做别的类型处理，则必须**显式地**使用类型转换。

## 11.2 C++中的引用

**引用**(**reference**)(`&`)就像能自动地被编译器间接引用的常量型指针。它通常用于函数的参数表中和函数的返回值，但也可以独立使用。例如：

> 代码示例：
[C11_01_FreeStandingReferences.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/11.%20Reference%20and%20the%20Copy-Constructor/C11_01_FreeStandingReferences.cpp)

```C++
    // C11_01_FreeStandingReferences.cpp
    #include<iostream>
    using namespace std;

    // Ordinary free-standing reference:
    int y;
    int& r = y;

    // when a reference is created, it must be initialized to a live object
    // However, you can also say:
    const int& q = 12;  // (1)

    // References are tied to someone eles's storage:
    int x = 0;  // (2)
    int& a = x; // (3)

    int main()
    {
        cout << "x = " << x << ", a = " << a << endl;
        a++;
        cout << "x = " << x << ", a = " << a << endl;
    }
```

在行(1)中，编译器分配了一个存储单元，它的值被初始化为12，于是这个引用就和这个存储单元联系上了。

使用引用时有一定的规则：

1) 当引用被创建时，它必须被初始化（指针则可以在任何时候被初始化）。
2) 一旦一个引用被初始化为指向一个对象，它就不能改变为另一个对象的引用（指针则可以在任何时候指向另一个对象）。
3) 不可能有NULL引用。必须确保引用是和一块合法的存储单元关联。

### 11.2.1 函数中的引用

最经常看见引用的地方是在函数参数和返回值中。当引用被用做函数参数时，在函数内任何对引用的更改将对函数外的参数产生改变。

如果从函数中返回一个引用，必须像从函数中返回一个指针一样对待。当函数返回时，无论引用关连的是什么都应该存在，否则，将不知道指向哪一个内存。

> 代码示例：
[C11_02_Reference.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/11.%20Reference%20and%20the%20Copy-Constructor/C11_02_Reference.cpp)

```C++
    // C11_02_Reference.cpp

    int* f(int* x)
    {
        (*x)++;
        return x;   // safe, x is outside this scope
    }

    int& g(int& x)
    {
        x++;
        return x;   // safe, outside this scope
    }

    int& h()
    {
        int q;
        // return q; // Error
        static int x;
        return x; // Safe, x lives outside this scope
    }

    int main()
    {
        int a = 0;
        f(&a);
        g(a);
    }
```

#### 11.2.1.1 常量引用

在函数参数中使用常屉引用特别重要。这是因为我们的函数也许会接受临时对象，这个临时对象是由另一个函数的返回值创立或由函数使用者显式地创立的。临时对象总是不变的，因此如果不使用常量引用，参数将不会被编译器接受。例如：

> 代码示例：
[C11_03_ConstReferenceArguments.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/11.%20Reference%20and%20the%20Copy-Constructor/C11_03_ConstReferenceArguments.cpp)

```C++
    // C11_03_ConstReferenceArguments.cpp

    // Passing references as const
    void f(int&){}
    void g(const int&) {}
    int main()
    {
        // f(1);   // Error
        g(1);
    }
```

#### 11.2.1.2 指针引用

如果想改变指针本身而不是它所指向的内容，在C++中，可以将函数参数变成指针的引用，不需要取得指针的地址：

> 代码示例：
[C11_04_ReferenceToPointer.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/11.%20Reference%20and%20the%20Copy-Constructor/C11_04_ReferenceToPointer.cpp)

```C++
    // C11_04_ReferenceToPointer.cpp
    #include <iostream>
    using namespace std;
    void increment(int*& i) {i++;}

    int main() 
    {
        int* i = 0;
        cout << "i = " << i  << endl;
        increment(i);
        cout << "i = " << i << endl;
    }
```

### 11.2.2 参数传递准则

传值方式需要调用构造函数和析构函数，然而如果不想改变参数，则可通过常量引用传递，它仅需要将地址压栈。

事实上，只有一种情况不适合用传递地址方式，这就是当传值是惟一安全的途径，否则将会破坏对象时（不想修改外部对象，这不是调用者通常期望的）。

## 11.3 拷贝构造函数

拷贝构造函数，它常被称为`X(X&)`("X引用的X")。在函数调用时，这个构造函数是控制通过传值方式传递和返回用户定义类型的根本所在。

### 11.3.1 按值传递和返回

#### 11.3.1.1 传递和返回大对象

如果创建了一个类，希望通过传值方式传递该类的一个对象，编译器怎样知道做什么？例如：

> 代码示例：
[C11_05_PassingBigStructures.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/11.%20Reference%20and%20the%20Copy-Constructor/C11_05_PassingBigStructures.cpp)

```C++
    // C11_05_PassingBigStructures.cpp
    struct Big
    {
        char buf[100];
        int i;
        long d;
    }B, B2;

    Big bigfun(Big b)
    {
        b.i = 100;
        return b;
    }

    int main()
    {
        B2 = bigfun(B);
    }
```

正如我们猜测的，首先调用函数`bigfun()`，整个B的内容被压栈。

#### 11.3.1.2 函数调用栈框架

当编译器为函数调用产生代码时，它首先把所有的参数压栈，然后调用函数。在函数内部，产生代码，向下移动栈指针为函数局部变址提供存储单元。

#### 11.3.1.3 重入

#### 11.3.1.4 位拷贝与初始化

一个类在任何时候都知道它存在多少个对象。

> 代码示例：
[C11_06_HowMany.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/11.%20Reference%20and%20the%20Copy-Constructor/C11_06_HowMany.cpp)

```C++
    // C11_06_HowMany.cpp
    #include <fstream>
    #include <string>
    using namespace std;
    ofstream out("HowMany.out");

    class HowMany
    {
        static int objectCount;
    public:
        HowMany() {objectCount++;}
        static void print(const string& msg="")
        {
            if(msg.size() != 0) out << msg << ": ";
            out << "objectCount = " << objectCount << endl;
        }
        ~HowMany()
        {
            objectCount--;
            print("~HowMany()");
        }
    };

    int HowMany::objectCount = 0;

    // Pass and return By Value:
    HowMany f(HowMany x)
    {
        x.print("x argument inside f()");
        return x;
    }

    int main()
    {
        HowMany h;
        HowMany::print("after construction of h");
        HowMany h2 = f(h);
        HowMany::print("after call to f()");
    }
```

`HowMany`类包括一个静态变县`int objectCount`和一个用于报告这个变量的静态成员函数`print()`，这个函数有一个可选择的消息参数。每当一个对象产生时，构造函数增加记数，而对象销毁时，析构函数减小记数。

然而，输出并不是期望的那样：

```C++
    after construction of h: objectCount = 1
    x argument inside f(): objectCount = 1
    ~HowMany(): objectCount = 0
    after call to f(): objectCount = 0
    ~HowMany(): objectCount = -1
    ~HowMany(): objectCount = -2
```

在h生成以后，对象数是1， 这是对的。我们希望在`f()`调用后对象数是2，因为`h2`也在范围内。然而，对象数是0，这意味着发生了严重的错误。这从结尾两个析构函数执行后使得对象数变为负数的事实得到确认，有些事根本就不应该发生。

在函数`f()`通过按值传递方式传入参数那一处。原来的对象h存在于函数框架之外，同时在函数体内又增加了一个对象，这个对象是通过传值方式传入的对象的拷贝。然而，参数的传递是使用C的原始的位拷贝的概念，但C++ `HowMany`类需要真正的初始化来维护它的完整性。所以，默认的位拷贝不能达到预期的效果。

在对`f()`的调用的最后，当局部对象出了其范围时，析构函数就被调用，析构函数使`objectCount`减小。所以，在函数外面，`objectCount`等于0。`h2`对象的创建也是用位拷贝产生的，所以，构造函数在这里也没有调用。当对象h和h2出了它们的作用范围时，它们的析构函数就使`objectCount`值变为负值。

### 11.3.2 拷贝构造函数

若设计了拷贝构造函数，当从现有的对象创建新对象时，编译器将不使用位拷贝。编译器总是调用我们的拷贝构造函数。所以，如果没有设计拷贝构造函数，编译器将做一些判断，但可以选择完全接管这个过程的控制。

> 代码示例：
[C11_07_HowMany2.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/11.%20Reference%20and%20the%20Copy-Constructor/C11_07_HowMany2.cpp)

```C++
    // C11_06_HowMany.cpp
    // The copy-constructor
    #include <fstream>
    #include <string>
    using namespace std;
    ofstream out("HowMany2.out");

    class HowMany2
    {
        string name;    // Object identifier
        static int objectCount;
    public:
        HowMany2(const string& id="") : name(id) 
        {
            ++objectCount;
            print("HowMany2()");
        }
        void print(const string& msg="") const
        {
            if(msg.size() != 0) 
                out << msg << endl;
            out << '\t' << name << ": " << "objectCount = " << objectCount << endl;
        }
        ~HowMany2()
        {
            --objectCount;
            print("~HowMany2()");
        }
        // The copy-constructor
        HowMany2(const HowMany2& h) : name(h.name)
        {
            name += "Copy";
            ++objectCount;
            print("HowMany2(const HowMany2&)");
        }
    };

    int HowMany2::objectCount = 0;

    // Pass and return By Value:
    HowMany2 f(HowMany2 x)
    {
        x.print("x argument inside f()");
        out << "Returning from f()" << endl;
        return x;
    }

    int main()
    {
        HowMany2 h("h");
        out << "Entering f()" << endl;
        HowMany2 h2 = f(h);
        h2.print("h2 after call to f()");
        out << "Call f(), no return value" << endl;
        f(h);
        out << "After call to f()" << endl;
    }
```

添加一个小程序，使用iostream为任何文件加入行号：

> 代码示例：
[C11_08_Linenum.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/11.%20Reference%20and%20the%20Copy-Constructor/C11_08_Linenum.cpp)

```C++
    // C11_08_Linenum.cpp
    // Add line number
    #include "../require.h"
    #include <vector>
    #include <string>
    #include <fstream>
    #include <iostream>
    #include <cmath>
    using namespace std;

    int main(int argc, char* argv[])
    {
        requireArgs(argc, 1, "Usage: Linenum file\n"
            "Adds line numbers to file");
        ifstream in(argv[1]);
        assure(in, argv[1]);
        string line;
        vector<string> lines;
        while(getline(in, line))// Read in entire file
            lines.push_back(line);
        if(lines.size() == 0) return 0;
        int num = 0;
        // Number of lines in file determines width:
        const int width = int(log10(lines.size())) + 1;
        for(int i = 0; i < lines.size(); i++)
        {
            cout.setf(ios::right, ios::adjustfield);
            cout.width(width);
            cout << ++num << ") " << lines[i] << endl;
        }
    }
```

整个文件被读入`vector<string>`，当打印行号时，希望所有的行都能彼此对齐，这就要求在文件中调整行的数目，以使得各行号所允许的宽度是一致的。我们可以轻松地通用`vector::size()`决定行的数目，但我们真正所需要知道的是它们是否超过了10行、100行、1000行等。如果对文件的行数取以10为底的对数，把它转为整型并再加1，这样就可得到行的最大宽度。

`ostream`调用允许控制对齐方式(setf()函数)和输出的宽度(width()函数)。但是它们必须在每一行被输出时都要调用。

#### 11.3.2.1 临时对象

每当编译器为了正确地计算一个表达式而需要一个临时对象时，编译器可以创建一个。在这种情况下，编译器创建一个看不见的对象作为函数`f()`忽略了的返回值的目标地址。

### 11.3.3 默认拷贝构造函数

因为拷贝构造函数实现按值传递方式的参数传递和返回，所以在这种简单结构情况下，编译器将有效地创建一个默认拷贝构造函数。然而一切默认的都是原始行为：**位拷贝**。

当包括更复杂的类型时，如果没有创建拷贝构造函数，C++编译器也将自动地创建拷贝构造函数。然而，位拷贝并不能达到我们的意图。

为显示编译器采取的更聪明的方法，设想创建了一个新类，它是由某些现
有类的对象组成的。这个创建类的方法被称为**组合**(**composition**)，它是从现有类创建新类的方法之一。因为还不知道拷贝构造函数，所以没有创建它。下面的例子演示了当编译器为新类创建默认拷贝构造函数时，编译器做了哪些事。

> 代码示例：
[C11_09_DefaultCopyConstructor.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/11.%20Reference%20and%20the%20Copy-Constructor/C11_09_DefaultCopyConstructor.cpp)

```C++
    // C11_09_DefaultCopyConstructor.cpp
    // Automatic creation of the copy-constructor
    #include <iostream>
    #include <string>
    using namespace std;

    class WithCC    // with copy constructor
    {
    public:
        // Explicit default constructor required:
        WithCC() {}
        WithCC(const WithCC& ){
            cout << "WithCC(WithCC&)" << endl;
        }
    };

    class WoCC // without copy constructor
    {
        string id;
    public:
        WoCC(const string& ident = "") : id(ident) {}
        void print(const string& msg = "") const{
            if(msg.size() != 0) cout << msg << ": ";
            cout << id << endl;
        }
    };

    class Composite
    {
        WithCC withcc;  // Embeded objects
        WoCC wocc;
    public:
        Composite() : wocc("Composite()") {}
        void print(const string& msg = "") const{
            wocc.print(msg);
        }
    };

    int main()
    {
        Composite c;
        c.print("Contents of c");
        cout << "Calling Composite copy-constructor" << endl;
        Composite c2 = c;   // Calls copy-constructor
        c2.print("Contents of c2");
    }
```

类`WithCC`有一个拷贝构造函数，这个函数只是简单地宣布它被调用，这引出了一个有趣的问题。在类`Composite`中，使用默认的构造函数创建一个`WithCC`类的对象。如果在类`WitbCC`中根本没有构造函数， 编译器将自动地创建一个默认的构造函数。不过在这种情况下，这个构造函数什么也不做；然而，*如果加了一个拷贝构造函数，我们就告诉了编译器我们将自己处理构造函数的创建，编译器将不再创建默认的构造函数，并且，除非我们显式地创建一个默认的构造函数，就如同为类WithCC所做的那样，否则将指示出错*。

类`WoCC`没有拷贝构造函数，但它的构造函数将在内部`string`中存储一个信息，这个信息可以使用`print()`函数打印出来。

类`Composite`并没有显示的定义拷贝构造函数，然而`Composite c2 = c;`语句使用了拷贝构造函数创建了一个对象。

为了对使用组合的类创建拷贝构造函数，编译器递归地为所有的成员对象和基类调用拷贝构造函数。如果成员对象还含有别的对象，那么后者的拷贝构造函数也将被调用。编译器获得一个拷贝构造函数的过程被称为**成员方法初始化**(**memberwise initialization**)。

### 11.3.4 替代拷贝构造函数的方法

通常仅当准备用*按值传递的方式传递类对象时*，才需要拷贝构造函数。如果不那么做时，就不需要拷贝构造函数。

#### 11.3.4.1 防止按值传递

有一个简单的技术防止通过按值传递方式传递：**声明一个私有拷贝构造函数**。如果用户试图用按值传递方式传递或返回对象，编译器将会发出一个出错信息。这是因为拷贝构造函数是私有的。因为己显式地声明我们接管了这项工作，所以编译器不再创建默认的拷贝构造函数。例如：

> 代码示例：
[C11_10_NoCopyConstruction.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/11.%20Reference%20and%20the%20Copy-Constructor/C11_10_NoCopyConstruction.cpp)

```C++
    //C11_10_NoCopyConstruction.cpp
    // Preventing copy-construction
    class NoCC
    {
        int i;
        NoCC(const NoCC&);  // No definition
    public:
        NoCC(int ii = 0) : i(ii) {}
    };

    void f(NoCC);

    int main()
    {
        NoCC n;
        // f(n); // Error: copy-constructor called
        // NoCC n2 = n;
        // NoCC n3(n);
    }
```

#### 11.3.4.2 改变外部对象的函数

引用语法比指针语法好用，但对于读者来说，它却使意思变得模糊。例如，在`iostreams`库函数中，一个重载版函数`get()`是用一个`char&`作为参数，这个函数的作用是通过插入`get()`的结果而改变它的参数。然而，当阅读使用这个函数的代码时，我们不会立即明白外面的对象正被改变：

```C++
    char c;
    cin.get(c);
```

相反，此函数调用看起来更像是按值传递方式传递，暗示着外部对象没有被改变。

正因为如此，当传递一个可被修改的参数地址时，从代码维护的观点看，使用指针可能更安全些。如果总是应用`const`引用传递地址，除非打算通过地址修改外部对象（这个地址通过非`const`指针传递），这样读者更容易读懂我们的代码。

## 11.4 指向成员的指针

指针是指向一些内存地址的变量，既可以是数据的地址也可以是函数的地址。所以，可以在运行时改变指针指向的内容。C++的**成员指针**(**pointer-to-member**)遵从同样的概念。这里麻烦的是所有的指针需要地址，**但在类内部是没有地址的**；选择一个类的成员意味着在类中偏移。只有把这个偏移和具体对象的开始地址结合，才能得到实际地址。**成员指针的语法要求选择一个对象的同时间接引用成员指针**。

考虑一个简单的结构：如果有一个这样结构的指针sp和对象so，可以通过下面方法选择成员：

> 代码示例：
[C11_11_SimpleStructure.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/11.%20Reference%20and%20the%20Copy-Constructor/C11_11_SimpleStructure.cpp)

```C++
    // C11_11_SimpleStructure.cpp
    struct Simple {int a;};

    int main()
    {
        Simple so, *sp = &so;
        sp->a;
        so.a;
    }
```

考虑如果有一个指向一个类对象成员的指针，如果假设它代表对象内一定的偏移，将会发生什么？为了取得指针指向的内容，必须用`*`号间接引用。但是，它只是一个对象内的偏移，所以必须也要指定那个对象。因此，`*`号要和间接引用的对象结合。所以，对于指向一个对象的指针，新的语法变为`->*`，对于一个对象或引用，则为`.*`，如下所示。

```C++
    objectPointer->*pointerToMember = 47;
    object.*pointerToMember = 47;
```

`pointerToMember`它像任何一个指针，定义时必须说出它指向什么类型。并且，在定义中也要使用一个`*`号。惟一的区别只是它必须说出这个成员指针使用什么类的对象。当然，这是用类名和作用域运算符实现的，如：`int ObjectClass::*pointerToMember;`

定义一个名字为`pointerToMember`的成员指针，该指针可以指向在`ObjectCiass`类中的任一`int`类型的成员。还可以在定义的时候初始化这个成员指针:`int ObjectClass::*pointerToMember = &ObjectClass::a;`

因为仅仅提到了一个类而非那个类的对象，所以没有`ObjectClass::a`的确切“地址”。因而，`&ObjectClass::a`仅是作为成员指针的语法被使用。

下面例子说明了如何建立和使用指向数据成员的指针：

> 代码示例：
[C11_12_PointerToMemberData.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/11.%20Reference%20and%20the%20Copy-Constructor/C11_12_PointerToMemberData.cpp)

```C++
    // C11_12_PointerToMemberData.cpp
    #include <iostream>
    using namespace std;
    class Data
    {
    public:
        int a, b, c;
        void print() const
        {
            cout << "a = " << a << ", b = " 
                << b << ", c = " << c << endl;
        }
    };

    int main()
    {
        Data d, *dp = &d;
        int Data::*pmInt = &Data::a;
        dp->*pmInt = 47;
        pmInt = &Data::b;
        d.*pmInt = 48;
        pmInt = &Data::c;
        dp->*pmInt = 49;
        dp->print();
    }
```

### 11.4.1 函数

指向函数的指针定义如下：`int (*fp)(float);`

`(*fp)`的圆括号用来迫使编译器正确判断定义。没有圆括号，这个表达式就是一个返回`int*`值的函数。

为了定义和使用成员函数的指针，圆括号扮演同样重要的角色。假设在一个结构内有一个函数，通过**给普通函数插入类名和作用域运算符**就可以定义一个指向成员函数的指针。

> 代码示例：
[C11_13_PmemFunDefinition.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/11.%20Reference%20and%20the%20Copy-Constructor/C11_13_PmemFunDefinition.cpp)

```C++
    // C11_13_PmemFunDefinition.cpp
    class Simple2
    {
    public:
        int f(float) const { return 1;}
    };

    int (Simple2::*fp)(float) const;
    int (Simple2::*fp2)(float) const = &Simple2::f;
    int main()
    {
        fp = &Simple2::f;
    }
```

从对`fp2`定义可以看出，一个成员指针可以在它创建的时候被初始化，或者也可在其他任何时候。不像非成员函数，**当获取成员函数的地址时，符号`&`不是可选**的。但是，可以给出不含参数列表的函数标识符，因为重载方案可以由成员指针的类型所决定。

#### 11.4.1.1 一个例子

成员指针也一样，它允许在运行时选择一个成员。特别的，**当类只有公有成员函数（数据成员通常被认为是内部实现的一部分）时，就可以用指针在运行时选择成员函数**，下面的例子正是这样：

> 代码示例：
[C11_14_PointerToMemberFunction.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/11.%20Reference%20and%20the%20Copy-Constructor/C11_14_PointerToMemberFunction.cpp)

```C++
    // C11_14_PointerToMemberFunction.cpp
    #include <iostream>
    using namespace std;

    class Widget
    {
    public:
        void f(int) const { cout << "Widget::f()\n"; }
        void g(int) const { cout << "Widget::g()\n"; }
        void h(int) const { cout << "Widget::h()\n"; }
        void i(int) const { cout << "Widget::i()\n"; }
    };

    int main()
    {
        Widget w;
        Widget* wp = &w;
        void (Widget::*pmem)(int) const = &Widget::h;
        (w.*pmem)(1);
        (wp->*pmem)(2);
    }
```

当然，期望一般用户创建如此复杂的表达式不是很合乎情理的。如果用户必须直接操作成员指针，那么`typedef`是适合的:

> 代码示例：
[C11_15_PointerToMemberFunction2.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/11.%20Reference%20and%20the%20Copy-Constructor/C11_12_PointerToMemberFunction2.cpp)

```C++
    // C11_15_PointerToMemberFunction2.cpp
    #include <iostream>
    using namespace std;
    class Widget
    {
        void f(int) const { cout << "Widget::f()\n"; }
        void g(int) const { cout << "Widget::g()\n"; }
        void h(int) const { cout << "Widget::h()\n"; }
        void i(int) const { cout << "Widget::i()\n"; }
        enum { cnt = 4 };
        void (Widget::*fptr[cnt])(int) const;
    public:
        Widget()
        {
            fptr[0] = &Widget::f;
            fptr[1] = &Widget::g;
            fptr[2] = &Widget::h;
            fptr[3] = &Widget::i;
        }
        void select(int i, int j)
        {
            if(i < 0 || i >= cnt) return;
            (this->*fptr[i])(j);
        }
        int count() {return cnt;}
    };

    int main()
    {
        Widget w;
        for(int i = 0; i < w.count(); i++)
            w.select(i, 47);
    }
```

在类接口和`main()`函数里，可以看到，包括函数本身在内的整个实现被隐藏了。

## 11.5 小结

拷贝构造函数采用相同类型的已存在对象的引用作为它的参数，它可以被用来从现有的对象创建新对象。

指向成员的指针和普通指针一样具有相同的功能：可以在运行时选取特定存储单元（数据或函数）。指向成员的指针只和类成员一起工作，而不是和全局数据或函数。通过使用指向成员的指针，我们的程序设计可以在运行时灵活地改变行为。
