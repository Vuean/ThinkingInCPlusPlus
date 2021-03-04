# 第14章 继承和组合

C++最重要的特征之一是代码重用。在本章中，我们将看到两种完成这项
任务的方法。第一种方法很直接：我们简单地在新类中创建已存在类的对象。因为新类是由已存在类的对象组合而成，所以这种方法称为**组合**(**composition**)。第二种方法要复杂些。我们创建一个新类作为一个已存在类的类型。我们不修改已存在的类，而是采取这个已存在类的形式，并将代码加入其中。这种巧妙的方法称为**继承**(**inheritance**)，其中大量的工作是由编译器完成。

## 14.1 组合语法

实际上，我们一直都在用组合创建类，只不过是在用内部数据类型（有时用string）组合新类。

> 代码示例：
[C14_01_Useful.h](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/14.%20Inheritance%20Composition/C14_01_Useful.h)

```C++
    // C14_01_Useful.cpp
    // A class to reuse
    #ifndef USEFUL_H
    #define USEFUL_H

    class X
    {
        int i;
    public:
        X() {i = 0;}
        void set(int ii) {i = ii;}
        int read() const {return i;}
        int premute() {return i = i * 47;}
    };

    #endif // USEFUL_H

```

在X类中，数值成员是私有的，所以将类型X的一个对象作为公共对象嵌入到一个新类内部，这是绝对安全的。这样就使得新类的接口很简单。

> 代码示例：
[C14_02_Composition.cpp](https://github.com/Vuean/ThinkingInCPlusPlus/blob/master/14.%20Inheritance%20Composition/C14_02_Composition.cpp)

```C++

```