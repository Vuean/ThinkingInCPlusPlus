// C04: C4_03_CPPLib.h
struct Statsh{
    int size;       // size of each space
    int quantity;   // number of storage space
    int next;       // NEXT EMPTY SPACE
    // Dynamically allocated array of bytes:
    unsigned char* storage;

    void initialize(int size);
    void cleanup();
    int add(const char* element);
    int count();
    void inflate(int increase);
};


