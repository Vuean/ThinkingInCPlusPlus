// C13_02_Tree.h
#ifndef TREE_H
#define TREE_H
#include <iostream>

class Tree
{
    int height;
public:
    Tree(int treeHeight) : height(treeHeight) {}
    ~Tree() {std::cout << "~Tree() delete t";}
    friend std::ostream& operator<<(std::ostream& os, const Tree* t)
    {
        return os << "Tree height is: " << t->height << std::endl;
    }
};
#endif // TREE_H