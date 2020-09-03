#include <iostream>
using namespace std;

int func1(double d1)
{
    cout << "Double value: " << d1 << endl;
    cout << "Int value: " << (int)(d1) << endl;
    return (int)(d1*10);
}

int main()
{
    int (*f_ptr)(double);
    f_ptr = func1;
    int result = (*f_ptr)(3.14);
    cout << "Result is: " << result << endl;
    return 0;
}