// C04: C4_01_CLib.h
// Header file for a C-like library
// An array-like entity created at runtime

typedef struct CStatshTag {
    int size;       // size of each space
    int quantity;   // number of storage space
    int next;       // NEXT EMPTY SPACE
    // Dynamically allocated array of bytes:
    unsigned char* storage;
}CStash;

void initialize(CStash* s, int size);
void cleanup(CStash* s);
int add(CStash* s, const char* element);
int count(CStash* s);
void inflate(CStash* s, int increase);
