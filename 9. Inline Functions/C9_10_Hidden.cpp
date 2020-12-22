// C9_10_Hidden.cpp
// Hidden activities in inlines
#include <iostream>
using namespace std;

class Member
{
    int i, j, k;
public:
    Member(int x = 0) : i(x), j(x), k(x) {}
    ~Member() {cout << "~Member()" << endl;}
};

class WithMembers
{
    Member q, r, s;
    int i;
public:
    WithMembers(int ii) : i(ii) {}
    ~WithMembers() {cout << "~WithMembers" << endl;}
};

int main()
{
    WithMembers wm(1);
}