#include <iostream>
using namespace std;

class A
{
public:
    A() {}
private:
// 调用时，显示拷贝构造函数已声明，但不可访问
    A(const A& tmp);
};

void f(A a) {}

int main()
{
    A a;
    f(a);
}