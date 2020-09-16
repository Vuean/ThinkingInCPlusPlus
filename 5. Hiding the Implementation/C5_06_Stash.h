// C05:C5_06_Stash.h
// Converted to use access control
#ifndef C5_06_STASH_H
#define C5_06_STASH_H
class Stash
{
    int size;       // size of each space
    int quantity;   // number of storage spaces
    int next;       // next empty space
    // Dynamically allocated array of bytes:
    unsigned char* storage;
    void inflate (int increase);
public:
    void initialize(int size);
    void cleanup();
    int add(void* element);
    void* fetch(int index);
    int count();
};

#endif // C5_06_STASH_H