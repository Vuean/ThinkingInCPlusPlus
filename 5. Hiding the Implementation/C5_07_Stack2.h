// C05: C5_07_Stack2.h
// Nested structs via linked list

#ifndef C5_07_STACK2_H
#define C5_07_STACK2_H

class Stack {
    struct Link{
        void* data;
        Link* next;
        void initialize(void* dat, Link* nxt);
    }* head;
public:
    void initialize();
    void push(void* dat);
    void* peek();
    void* pop();
    void cleanup();
};
#endif // C5_07_STACK2_H