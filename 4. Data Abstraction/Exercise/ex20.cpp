#include <iostream>
using namespace std;

struct s1{

};

struct s2{
    int i;
    long l;
    double d;
};

struct s3{
    int i;
    double d;
    long l;
    void f1();
    void f2();
};

void s3::f1() {}
void s3::f2() {}

struct s4{
    void f1();
    void f2();
};

void s4::f1() {}
void s4::f2() {}

int main()
{
    cout << "sizeof(s1) = " << sizeof(s1) << endl;
    cout << "sizeof(s2) = " << sizeof(s2) << endl;
    cout << "sizeof(s3) = " << sizeof(s3) << endl;
    cout << "sizeof(s4) = " << sizeof(s4) << endl;
}