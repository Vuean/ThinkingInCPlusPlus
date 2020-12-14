#ifndef STASH3_H
#define STASH3_H

class Stash3
{
    int size;
    int quantity;
    int next;
    unsigned char* storage;
    void inflate(int increase);
public:
    Stash3(int size, int quantity = 0);
    ~Stash3();
    int add(void* element);
    void* fetch(int index);
    int count();
};

#endif // STASH3_H