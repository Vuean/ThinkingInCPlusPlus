// C07: Stash3.h
// Function overloading
#ifndef STASH3_H
#define STASH3_H

class Stash
{
    int size;           // Size of each space
    int quantity;       // Number of storage spaces
    int next;           // Next empty space
    // Dynamically allocated array of bytes:
    unsigned char* storage;
    void inflate(int increase);
public:
    Stash(int size);    // Zero quantity
    Stash(int size, int initQuantity); 
    ~Stash();
    int add(void* element);
    void* fetch(int index);
    int count();
};

#endif // STASH3_H