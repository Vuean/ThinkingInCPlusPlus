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
    // Selection ends a union(分号), like a struct
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