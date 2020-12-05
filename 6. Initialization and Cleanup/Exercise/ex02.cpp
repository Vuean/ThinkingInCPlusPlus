#include <iostream>
using namespace std;

class Simple
{
    int i;
public:
    Simple();
    Simple(int value);
    void print();
    ~Simple();
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

Simple::~Simple()
{
    print();
    cout << "Simple::~Simple()" << endl;
}

int main()
{
    Simple s1;
    if(1)
    {
        Simple s2(2);
    }
}