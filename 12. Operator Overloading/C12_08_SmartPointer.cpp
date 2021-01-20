// C12_08_SmartPointer.cpp
#include <iostream>
#include <vector>
#include "../require.h"
using namespace std;

class Obj
{
    static int i, j;
public:
    void f() const {cout << i++ << endl;}
    void g() const {cout << j++ << endl;}
};

// Static member definitions:
int Obj::i = 47;
int Obj::j = 11;

// Container:
class ObjContainer
{
    vector<Obj*> a;
public:
    void add(Obj* obj) {a.push_back(obj);}
    friend class SmartPointer;
};

class SmartPointer
{
    ObjContainer& oc;
    int index;
public:
    SmartPointer(ObjContainer& objc) : oc(objc)
    {
        index = 0;
    }
    // Return value indicates end of list:
    bool operator++()
    {
        if(index >= oc.a.size()) return false;
        if(oc.a[++index] == 0) return false;
        return true;
    }
    bool operator++(int)
    {
        return operator++();
    }
    Obj* operator->() const
    {
        require(oc.a[index] != 0, "Zero value "
            "returned by SmartPointer::operator->()");
        return oc.a[index];
    }
};

int main()
{
    const int sz = 10;
    Obj o[sz];
    ObjContainer oc;
    for(int i = 0; i < sz; i++)
        oc.add(&o[i]);
    SmartPointer sp(oc);    // Create an iterator
    do{
        sp->f();    // Pointer dereference operator call
        sp->g();
    }while(sp++);
}