// C11_06_HowMany.cpp
// The copy-constructor
#include <fstream>
#include <string>
using namespace std;
ofstream out("HowMany2.out");

class HowMany2
{
    string name;    // Object identifier
    static int objectCount;
public:
    HowMany2(const string& id="") : name(id) 
    {
        ++objectCount;
        print("HowMany2()");
    }
    void print(const string& msg="") const
    {
        if(msg.size() != 0) 
            out << msg << endl;
        out << '\t' << name << ": " << "objectCount = " << objectCount << endl;
    }
    ~HowMany2()
    {
        --objectCount;
        print("~HowMany2()");
    }
    // The copy-constructor
    HowMany2(const HowMany2& h) : name(h.name)
    {
        name += "Copy";
        ++objectCount;
        print("HowMany2(const HowMany2&)");
    }
};

int HowMany2::objectCount = 0;

// Pass and return By Value:
HowMany2 f(HowMany2 x)
{
    x.print("x argument inside f()");
    out << "Returning from f()" << endl;
    return x;
}

int main()
{
    HowMany2 h("h");
    out << "Entering f()" << endl;
    HowMany2 h2 = f(h);
    h2.print("h2 after call to f()");
    out << "Call f(), no return value" << endl;
    f(h);
    out << "After call to f()" << endl;
}