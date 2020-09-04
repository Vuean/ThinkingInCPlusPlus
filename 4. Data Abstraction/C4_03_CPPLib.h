// C04: C4_03_CPPLib.h
struct Stash{
    int size;       // size of each space
    int quantity;   // number of storage space
    int next;       // NEXT EMPTY SPACE
    // Dynamically allocated array of bytes:
    unsigned char* storage;

    void initialize(int size);
    void cleanup();
    int add(const void* element);
    void* fetch(int index);
    int count();
    void inflate(int increase);
};


