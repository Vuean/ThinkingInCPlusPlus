// C14_01_Useful.cpp
// A class to reuse
#ifndef USEFUL_H
#define USEFUL_H

class X
{
    int i;
public:
    X() {i = 0;}
    void set(int ii) {i = ii;}
    int read() const {return i;}
    int premute() {return i = i * 47;}
};

#endif // USEFUL_H
