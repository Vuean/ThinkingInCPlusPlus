// C13_01_MallocClass.cpp
// Malloc with class objects
// What you'd have to do if not for "new"
#include "../require.h"
#include <cstdlib>  // malloc() & free()
#include <cstring>
#include <iostream>
using namespace std;

class Obj
{
    int i, j, k;
    enum {sz = 100};
    char buf[sz];
public:
    void initialize()
    {
        // can't use constructor
        cout << "Initializing Obj" << endl;
        i = j = k = 0;
        memset(buf, 0, sz);
    }
    void destory() const
    {
        // can't use destructor
        cout << "Destoring Obj" << endl;
    }
};

int main()
{
    Obj* obj = (Obj*)malloc(sizeof(Obj));
    require(obj != 0);
    obj->initialize();
    // ... sometime later
    obj->destory();
    free(obj);
}