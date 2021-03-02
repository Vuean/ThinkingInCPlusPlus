// C13_09_NoMemory.cpp
// Constructor isn't called if new fails
#include <iostream>
#include <new>
using namespace std;

class NoMemory
{
public:
    NoMemory()
    {
        cout << "NoMemory::NoMemory()" << endl;
    }
    void* operator new(size_t sz) throw(bad_alloc)
    {
        cout << "NoMemory::operator new" << endl;
        throw bad_alloc();
    }
};

int main()
{
    NoMemory* nm = 0;
    try{
        nm = new NoMemory();
    }catch(bad_alloc)
    {
        cerr << "out of memory exception" << endl;
    }
    cout << "nm = " << nm << endl;
}