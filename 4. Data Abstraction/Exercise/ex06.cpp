#include <iostream>
using namespace std;

struct s1{
    int a;
    void func1(int value);
    void func2();
};

void s1::func1(int value)
{
    this->a = value;
}

void s1::func2()
{
    cout << "value is " << this->a << endl;
}

int main()
{
    s1 s1ptr;
    s1ptr.func1(2020);
    s1ptr.func2();
    return 0;
}