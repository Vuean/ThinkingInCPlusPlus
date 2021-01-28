#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Bird
{
    string s;
    static int i;
    friend ostream& operator<<(ostream& os, const Bird& obj);
public:
    Bird()
    {
        ostringstream ss;
        ss << "Bird#" << ++i;
        s = ss.str();

        cout << s << ": constructor called." << endl;
        countObjects();
    }
    Bird(const Bird& b)
    {
        s = b.s;
        ++i;
        cout << s << ": copy constructor called." << endl;
        countObjects();
    }
    ~Bird()
    {
        --i;
        cout << s << ": destructor called." << endl;
        countObjects();
    }
    Bird& operator=(const Bird& right)
    {
        cout << s << "operator=() called." << endl;
        if(this == &right)
            return *this;
        s = right.s;
        countObjects();
    }
    void countObjects() {cout << "Bird instanses: " << i << endl;}
};

int Bird::i = 0;

ostream& operator<<(ostream& out, const Bird& obj)
{
    out << obj.s;
    return out;
}

void someFunc(Bird b) {}

int main()
{
    Bird a, b, c;
    cout << a << ", " << b << ", " << c << endl;
    c = a;
    someFunc(b);
    cout << a << ", " << b << ", " << c << endl;
}
