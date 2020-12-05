// C07: Stash3.cpp
#include "C7_01_Stash3.h"
#include "../require.h"
#include <iostream>
#include <cassert>
using namespace std;
const int increment = 100;

Stash::Stash(int sz)
{
    size = sz;
    quantity = 0;
    next = 0;
    storage = 0;
}

Stash::Stash(int sz, int initQuantity)
{
    size = sz;
    quantity = initQuantity;
    next = 0;
    storage = 0;
    inflate(initQuantity);
}

Stash::~Stash()
{
    if(storage != 0)
    {
        cout << "freeing storage" << endl;
        delete [] storage;
    }
}

int Stash::add(void* element)
{
    if(next >= quantity)    // Enough space left?
        inflate(increment);
    // Copy element into storage
    // starting at the next empty space:
    int startBytes = next * size;
    unsigned char* e = (unsigned char*)element;
    for(int i = 0; i < size; i++)
        storage[startBytes + i] = e[i];
    next++;
    return (next - 1);
}

void* Stash::fetch(int index)
{
    require(0 <= index, "Stash::fetch (-)index");
    if(index >= next)
        return 0;   // To indicate the end
    // Produce pointer to desired element:
    return &(storage[index * size]);
}

int Stash::count()
{
    return next;    // Number of elements in CStash
}

void Stash::inflate(int increase)
{
    require(increase > 0, "Stash::inflate zero or negative increase");
    int newQuantity = quantity + increase;
    int newBytes = newQuantity * size;
    int oldBytes = quantity * size;
    unsigned char* b = new unsigned char[newBytes];
    for(int i = 0; i < oldBytes; i++)
        b[i] = storage[i];  // Copy old to new
    delete [] (storage);    // Delete old storage
    storage = b;    // point to new memory
    quantity = newQuantity;
}