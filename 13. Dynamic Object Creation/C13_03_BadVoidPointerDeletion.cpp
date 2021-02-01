// C13_03_BadVoidPointerDeletion.cpp
// Deleting void pointers can cause memory leaks
#include <iostream>
using namespace std;

class Object
{
    void* data; // some storage
    const int size;
    const char id;
public:
    Object(int sz, char c) : size(sz), id(c)
    {
        data = new char[size];
        cout << "constructing object" << id 
             << ", size = " << size << endl;
    }
    ~Object()
    {
        cout << "Destructing object" << id << endl;
        delete []data;  // OK just release storage
        // no destructor calls are necessary
    }
};

int main()
{
    Object* a = new Object(40, 'a');
    delete a;
    void* b = new Object(40, 'b');
    delete b;
}
