#include "Stash3.h"
#include "../../require.h"
#include <iostream>
#include <cassert>
using namespace std;

const int increment = 100;

Stash3::Stash3(int sz, int initQuantity)
{
    size = sz;
    quantity = 0;
    next = 0;
    storage = 0;
    inflate(initQuantity);
}

Stash3::~Stash3()
{
    if(storage != 0)
    {
        cout << "freshing storage" << endl;
        delete []storage;
    }
}

int Stash3::add(void* element)
{
    if(next >= quantity)
        inflate(increment);
    int startBytes = next * size;
    unsigned char* e = (unsigned char*) element;
    for(int i = 0; i < size; i++)
        storage[startBytes + i] = e[i];
    next++;
    return (next - 1);
}

void* Stash3::fetch(int index)
{
    require(0 <= index, "Stash::fetch (-)index");
    if(index >= next)
        return 0;
    return &(storage[index * size]);
}

int Stash3::count() 
{
	return next;
}

void Stash3::inflate(int increase)
{
    assert(increase > 0);
    if(increase == 0) return;
    int newQuantity = quantity + increase;
    int newBytes = newQuantity * size;
    int oldBytes = quantity * size;
    unsigned char* b = new unsigned char[newBytes];
    for(int i = 0; i < oldBytes; i++)
        b[i] = storage[i];
    delete []storage;
    storage = b;
    quantity = newQuantity;
}