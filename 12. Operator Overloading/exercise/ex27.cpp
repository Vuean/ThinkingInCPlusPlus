#include <iostream>
#include <vector>
using namespace std;

class Obj
{
    static int i, j;
public:
    void f() const {cout << i++ << endl;}
    void g() const {cout << j++ << endl;}
    typedef void (Obj::*PMF)(void);

    class FunctionObject 
    {
        Obj* ptr;
        PMF pmem;
     public:
        // Save the object pointer and member pointer
        FunctionObject(Obj* wp, PMF pmf)
        : ptr(wp), pmem(pmf) 
        {
            cout << "FunctionObject constructor\n";
        }
        // Make the call using the object pointer
        // and member pointer
        void operator()(void) const 
        {
            cout << "FunctionObject::operator()\n";
            (ptr->*pmem)(); // Make the call
        }
    };

    FunctionObject operator->*(PMF pmf) 
    {
        cout << "operator->*" << endl;
        return FunctionObject(this, pmf);
    }
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
    class SmartPointer;
    friend SmartPointer;
    class SmartPointer
    {
        ObjContainer& oc;
        unsigned int index;
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
            return oc.a[index];
        }
    };
    // Function to produce a smart pointer that points to
    // the beginning og the ObjContainer:
    SmartPointer begin()
    {
        return SmartPointer(*this);
    }
};

int main()
{
    const int sz = 10;
    Obj o[sz];
    ObjContainer oc;
    for(int i = 0; i < sz; i++)
        oc.add(&o[i]);
    ObjContainer::SmartPointer sp = oc.begin();    // Create an iterator
    do{
        sp->f();    // Pointer dereference operator call
        sp->g();
    }while(++sp);
}