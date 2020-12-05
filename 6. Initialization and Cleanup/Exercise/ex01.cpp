#include <iostream>
using namespace std;

class Simple
{
    int i;
public:
    Simple();
    Simple(int value);
    void print();
};

Simple::Simple()
{
    cout << "Simple::Simple()" << endl;
}

Simple::Simple(int value)
{
    i = value;
    cout << "Simple::Simple(int value)" << endl;
}

void Simple::print()
{
    cout << "print the value hidden by Class Simple is " << i << endl;
}

int main()
{
    Simple s1;
    Simple s2(2);
}