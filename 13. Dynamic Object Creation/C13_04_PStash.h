// C13_04_PStash.h
#ifndef PSTASH_H
#define PSTASH_H

class PStash
{
    int quantity;   // Number of storage spaces
    int next;       // Next empty space
    // Pointer storage
    void** storage; 
    void inflate(int increase);
public:
    PStash() : quantity(0), storage(0), next(0) {}
    ~PStash();
    int add(void* element);
    void* operator[](int index) const;
    // Remove the reference from this PStash:
    void* remove(int index);
    // Number of elements in Stash:
    int count() const {return next;}
};
#endif //PSTASH_H