// C07:Mem.h
#ifndef MEM_H
#define MEM_H

 typedef unsigned char bytes;

 class Mem
 {
    bytes* mem;
    int size;
    void ensureMinSize(int minSize);
public:
    Mem();
    Mem(int sz);
    ~Mem();
    int msize();
    bytes* pointer();
    bytes* pointer(int minSize);
 };

#endif // MEM_H