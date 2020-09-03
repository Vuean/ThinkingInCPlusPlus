#include <iostream>
using namespace std;

float func1(char c)
{
    cout << "Function 1: " << c << endl;
    return 3.14;
}

float (*(func2(int)))(char)
{
    cout << "Function 2: " << endl;
    return func1;
}

int main()
{
    float (*(*f2_ptr)(int))(char);
    f2_ptr = func2;

    float (*f1_ptr)(char);
    f1_ptr = (*f2_ptr)(1212);
    (*f1_ptr)('a');
}