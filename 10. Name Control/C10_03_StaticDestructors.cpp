// C10_03_StaticDestructors.cpp
// Static object destructors
#include <fstream>
using namespace std;
ofstream out("statdest.out");

class Obj
{
    char c; // Identifier
public:
    Obj(char cc) : c(cc) 
    {
        out << "Obj::Obj() for " << c << endl;
    }
    ~Obj()
    {
        out << "Obj::~Obj() for " << c << endl;
    }
};

Obj a('a'); // Global (static storage)
// Constructor & destructor always called

void f()
{
    static Obj b('b');
}

void g()
{
    Obj c('c');
}

int main()
{
    out << "inside main()" << endl;
    f();    // Calls static constructor for b
    g();
    out << "leaving main()" << endl;
}