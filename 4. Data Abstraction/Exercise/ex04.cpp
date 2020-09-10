#include <iostream>
using namespace std;

struct s1{
    int a;
};

void func1(s1 *s1ptr, int value)
{
    s1ptr->a = value;
}

void func2(s1 *s1ptr)
{
    cout << s1ptr->a << endl;
}

int main()
{
    s1 s1ptr;
    ::func1(&s1ptr, 2020);
    ::func2(&s1ptr);
    return 0;
}