#include <iostream>
using namespace std;

struct s1
{

};

union u1{

};

enum e1{

};

int main()
{
    cout << "sizeof(s1) = " << sizeof(s1) << endl;
    cout << "sizeof(u1) = " << sizeof(u1) << endl;
    cout << "sizeof(e1) = " << sizeof(e1) << endl;
    return 0;
}