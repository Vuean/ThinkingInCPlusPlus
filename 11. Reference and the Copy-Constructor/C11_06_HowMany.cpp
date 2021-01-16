// C11_06_HowMany.cpp
#include <fstream>
#include <string>
using namespace std;
ofstream out("HowMany.out");

class HowMany
{
    static int objectCount;
public:
    HowMany() {objectCount++;}
    static void print(const string& msg="")
    {
        if(msg.size() != 0) out << msg << ": ";
        out << "objectCount = " << objectCount << endl;
    }
    ~HowMany()
    {
        objectCount--;
        print("~HowMany()");
    }
};

int HowMany::objectCount = 0;

// Pass and return By Value:
HowMany f(HowMany x)
{
    x.print("x argument inside f()");
    return x;
}

int main()
{
    HowMany h;
    HowMany::print("after construction of h");
    HowMany h2 = f(h);
    HowMany::print("after call to f()");
}