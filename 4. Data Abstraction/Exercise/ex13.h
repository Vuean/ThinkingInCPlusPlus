#ifndef EX13_H
#define EX13_H

#include <iostream>
#include <vector>

struct Vedio
{
    std::string name;
    float duration; // Ê±³¤
    double cost;
    std::vector<std::string> actors;
    bool isReleased;

    void initialize();
    void print();
    void release();
};

#endif // EX13_H