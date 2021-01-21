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
};

int main()
{
    Dog m;
    Dog::PMF pmf = &Dog::run;
    cout << (m->*pmf)(1) << endl;
    pmf = &Dog::sleep;
    cout << (m->*pmf)(2) << endl;
    pmf = &Dog::eat;
    cout << (m->*pmf)(3) << endl;
}