#include <iostream>
#include <string>
using namespace std;
class One
{
    string s1;
public:
    One(string s = "") : s1(s) {}
    string getStr() const { return s1;}
};

class Two
{
    One o;
public:
    Two(string str) : o(str) {}
    void print() const {cout << o.getStr() << endl;}
};

int main()
{
    Two t1("first");
    Two t2(t1);

    t1.print();
    t2.print();

    Two t3("third");
    Two t4 = t3;

    t3.print();
    t4.print();
}