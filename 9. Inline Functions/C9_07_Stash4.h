// C9_07_Stash4.h
#ifndef STASH4_H
#define STASH4_H
#include "../require.h"

class Stash
{
    int size;
    int quantity;
    int next;
    // Dynamically allocated array of bytes:
    unsigned char* storage;
    void inflate(int increase);
public:
    Stash(int sz) : size(sz), quantity(0), 
        next(0), storage(0) {}
    Stash(int sz, int initQuantity) : size(sz), quantity(0), 
        next(0), storage(0)
    {
        inflate(initQuantity);
    }
    Stash::~Stash()
    {
        if(storage != 0)
            delete []storage;
    }
    int add(void* element);
    void* fetch(int index) const
    {
        require(0 <= index, "Stash::fetch (-)index");
        if(index >= next)
            return 0;
        // produce pointer to desired element:
        return &(storage[index * size]);
    }
    int count() const {return next;}
}

#endif // STASH4_H