// C6_01_Constructor.cpp
// Constructors & destructors
#include <iostream>
using namespace std;

class Tree
{
    int height;
public:
    Tree(int initialHeight);    // Constructor
    ~Tree(); // Destructor
    void grow(int years);
    void printsize();
};

Tree::Tree(int initialHeight)
{
    height = initialHeight;
}

Tree::~Tree()
{
    cout << "inside Tree destructors" << endl;
    printsize();
}

void Tree::grow(int years){
    height += years;
}

void Tree::printsize()
{
    cout << "Tree heights is " << height << endl;
}

int main()
{
    cout << "before opening brace: " << endl;
    {
        Tree t(12);
        cout << "after Tree creation" << endl;
        t.printsize();
        t.grow(4);
        cout << "before closing brace: " << endl;
    }
    cout << "after closing brace: " << endl;
}

/*
    运行结果：
    before opening brace: 
    after Tree creation
    Tree heights is 12
    before closing brace:
    inside Tree destructors
    Tree heights is 16
    after closing brace:
*/