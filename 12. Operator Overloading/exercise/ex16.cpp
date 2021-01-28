#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Bird
{
    string name;
    static int count;
    int data;
    friend ostream& operator<<(ostream& os, const Bird& obj);
public:
    Bird() : data(0)
    {
        ostringstream ss;
        ss << "Bird#" << ++count;
        name = ss.str();
    }
    Bird(int x) : data(x)
    {
        ostringstream ss;
        ss << "Bird#" << ++count;
        name = ss.str();
    }
    Bird(const Bird& b)
    {
        name = b.name;
        data = b.data;
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
    const Bird operator+(const Bird& right) const { return Bird(data + right.data); }
    const Bird operator-(const Bird& right) const { return Bird(data - right.data); }
    const Bird operator*(const Bird& right) const { return Bird(data * right.data); }
    const Bird operator/(const Bird& right) const { return Bird(data / right.data); }
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
    BirdHouse(Bird a, Bird* b, Bird& c, int x = 0) : bObj(a), bPtr(b), bRef(c) {}
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
    Bird a(2), b(3), c(6);
    Bird d = a + b;
    Bird e = c - a;
    Bird f = b * c / a;


    BirdHouse h1(a, &b, c);
    BirdHouse h2(d, &e, f);

    cout << h1 << endl;
    cout << h2 << endl;
}