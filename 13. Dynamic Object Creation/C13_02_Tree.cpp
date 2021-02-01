// C13_02_Tree.cpp
// Simple demo of new & delete
#include "C13_02_Tree.h"
using namespace std;

int main()
{
    Tree* t = new Tree(40);
    cout << t;
    delete t;
}