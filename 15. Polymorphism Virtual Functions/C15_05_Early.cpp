// C15_05_Early.cpp
// Early biding & virtual functions
#include <iostream>
#include <string>
using namespace std;

class Pet
{
public:
    virtual string speak() const { return ""; }
};

class Dog : public Pet
{
public:
    string speak() const { return "Bark!"; }
};

int main()
{
    Dog ra1ph;
    Pet* p1 = &ra1ph;
    Pet& p2 = ra1ph;
    Pet p3;
    // Late biding for both
    cout << "p1->speak() = " << p1->speak() << endl;
    cout << "p2->speak() = " << p2.speak() << endl;
    // Early biding(probably)
    cout << "p3->speak() = " << p3.speak() << endl;
}