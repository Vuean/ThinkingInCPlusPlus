#include <iostream>
#include <string>
using namespace std;

class Test
{
    int x;
    string s;
    friend ostream& operator<<(ostream& out, const Test& obj);
public:
    Test(int xx, string str = "op= call.") : x(xx), s(str) {}

    Test& operator=(const Test& right)
    {
        if(this == &right)
            return *this;
        x = right.x;
        s = right.s;
        return *this;
    }
};

ostream& operator<<(ostream& os, const Test& obj)
{
    os << obj.x << " - " << obj.s;
    return os;
}

int main()
{
    Test t1(10, "test"), t2(20);
    cout << "t1 = " << t1
         << "\nt2 = " << t2 << endl;
    
    t1 = t2;
    cout << "t1 = t2;" 
         << "\nt1 = " << t1
         << "\nt2 = " << t2 << endl;
    return 0;
}