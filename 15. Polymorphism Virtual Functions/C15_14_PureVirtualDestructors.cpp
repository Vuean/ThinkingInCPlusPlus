// C15_14_PureVirtualDestructors.cpp
// Pure virtual destructors require a function body
#include <iostream>
using namespace std;

class Pet
{
public:
    virtual ~Pet() = 0;
};

Pet::~Pet()
{
    cout << "~Pet()" << endl;
}

class Dog : public Pet
{
public:
    ~Dog()
    {
        cout << "~Dog()" << endl;
    }
};

int main()
{
    Pet* p = new Dog;
    delete p;
}