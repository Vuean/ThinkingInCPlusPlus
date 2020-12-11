// C07:Mem.cpp
#include "C7_07_Mem.h"
#include <cstring>
using namespace std;

Mem::Mem()
{
    mem = 0;
    size = 0;
}

Mem::Mem(int sz)
{
    mem = 0;
    size = 0;
    ensureMinSize(sz);
}

Mem::~Mem() { delete []mem; }

void Mem::ensureMinSize(int minsize)
{
    if(size < minsize)
    {
        bytes* newmem = new bytes[minsize];
        memset(newmem + size, 0, minsize - size);
        memcpy(newmem, mem, size);
        delete []mem;
        mem = newmem;
        size = minsize;
    }
}

bytes* Mem::pointer() {return mem;}

bytes* Mem::pointer(int minSize)
{
    ensureMinSize(minSize);
    return mem;
}