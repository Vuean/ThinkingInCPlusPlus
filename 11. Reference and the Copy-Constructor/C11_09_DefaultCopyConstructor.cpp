// C11_09_DefaultCopyConstructor.cpp
// Automatic creation of the copy-constructor
#include <iostream>
#include <string>
using namespace std;

class WithCC    // with copy constructor
{
public:
    // Explicit default constructor required:
    WithCC() {}
    WithCC(const WithCC& ){
        cout << "WithCC(WithCC&)" << endl;
    }
};

class WoCC // without copy constructor
{
    string id;
public:
    WoCC(const string& ident = "") : id(ident) {}
    void print(const string& msg = "") const{
        if(msg.size() != 0) cout << msg << ": ";
        cout << id << endl;
    }
};

class Composite
{
    WithCC withcc;  // Embeded objects
    WoCC wocc;
public:
    Composite() : wocc("Composite()") {}
    void print(const string& msg = "") const{
        wocc.print(msg);
    }
};

int main()
{
    Composite c;
    c.print("Contents of c");
    cout << "Calling Composite copy-constructor" << endl;
    Composite c2 = c;   // Calls copy-constructor
    c2.print("Contents of c2");
}