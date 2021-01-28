// C12_10_PointerToMemberOperator.cpp
#include <iostream>
using namespace std;
class Dog
{
public:
    int run(int i) const
    {
        cout << "run\n";
        return i;
    }
    int eat(int i) const
    {
        cout << "eat\n";
        return i;
    }
    int sleep(int i) const
    {
        cout << "ZZZ\n";
        return i;
    }
    typedef int (Dog::*PMF)(int) const;
    typedef void(Dog::*PMF2)() const;
    // operator->* must return an object that has an operator()
    class FunctionObject
    {
        Dog* ptr;
        PMF pmem;
    public:
        // save the object pointer and member pointer
        FunctionObject(Dog* wp, PMF pmf)
            : ptr(wp), pmem(pmf)
        {
            cout << "FunctionObject constructor\n";
        }
        // Make the call using the object pointer and member pointer
        int operator()(int i) const
        {
            cout << "FunctionObject::operator()\n";
            return (ptr->*pmem)(i);
        }
    };
    FunctionObject operator->*(PMF pmf)
    {
        cout << "operator->*" << endl;
        return FunctionObject(this, pmf);
    }

    class FunctionObject2 
    {
        Dog* ptr;
        PMF2 pmem;
    public:
        // Save the object pointer and member pointer
        FunctionObject2(Dog* wp, PMF2 pmf)
            : ptr(wp), pmem(pmf) 
        {
            cout << "FunctionObject2 constructor\n";
        }
        // Make the call using the object pointer
        // and member pointer
        void operator()(void) const 
        {
            cout << "FunctionObject2::operator()\n";
            (ptr->*pmem)(); // Make the call
        }
    };
    FunctionObject2 operator->*(PMF2 pmf) 
    {
        cout << "operator->*" << endl;
        return FunctionObject2(this, pmf);
    }
};


int main()
{
    Dog w;
    Dog::PMF pmf = &Dog::run;
    cout << (w->*pmf)(1) << endl;
    pmf = &Dog::sleep;
    cout << (w->*pmf)(2) << endl;
    pmf = &Dog::eat;
    cout << (w->*pmf)(3) << endl;

    Dog w2;
    Dog::PMF2 pmf2 = &Dog::func1;
    (w2->*pmf2)();
    pmf2 = &Dog::func2;
    (w2->*pmf2)();
}