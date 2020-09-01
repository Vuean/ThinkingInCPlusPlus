#include <iostream>
#include <string>
using namespace std;

void func1(string* s1)
{
    *s1 = "func1(" + *s1 + ")";
    //cout << "func1(): " << *s1 << endl;
}

void func2(string& s2)
{
    s2 = "func2(" +s2 + ")";
    //cout << "func2(): " << s2 << endl;
}

int main()
{
    string ss1, ss2;
    ss1 = "C++";
    ss2 = "Python";

    func1(&ss1);
    cout << "func1(): " << ss1 << endl;

    func2(ss2);
    cout << "func2(): " << ss2 << endl;

    return 0;
}