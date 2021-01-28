#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Bird
{
    string name;
    static int count;
    friend ostream& operator<<(ostream& os, const Bird& obj);
public:
    Bird()
    {
        ostringstream ss;
        ss << "Bird#" << ++count;
        name = ss.str();
    }
    Bird(const Bird& b)
    {
        name = b.name;
        ++count;
    }
    ~Bird()
    {
        --count;
    }
    Bird& operator=(const Bird& right)
    {
        if(this == &right)
            return *this;
        name = right.name;
        return *this;
    }
};

int Bird::count = 0;

ostream& operator<<(ostream& os, const Bird& obj)
{
    os << obj.name;
}

class BirdHouse
{
    Bird bObj;
    Bird* bPtr;
    Bird& bRef;
    BirdHouse(const BirdHouse&);
    BirdHouse& operator=(const BirdHouse& right);
    friend ostream& operator<<(ostream& os, const BirdHouse& obj);
public:
    BirdHouse(Bird a, Bird* b, Bird& c) : bObj(a), bPtr(b), bRef(c) {}
};

ostream& operator<<(ostream& out, const BirdHouse& obj) 
{
    out << "\nObject: " << obj.bObj
        << "\nPointer: " << *obj.bPtr
        << "\nReference: " << obj.bRef;
    return out;
}

int main()
{
    Bird a, b, c;
    BirdHouse h(a, &b, c);

    cout << h << endl;
    
    c = b = a;
    cout << "\nc = b = a;\n"
         << h << endl;
}