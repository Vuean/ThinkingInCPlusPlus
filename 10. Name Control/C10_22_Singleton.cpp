// C10_22_Singleton.cpp
// Static member of same type, ensures that only one object
// of this type exists.
// Also referred to as the "Singleton" pattern
#include <iostream>
using namespace std;

class Egg
{
    static Egg e;
    int i;
    Egg(int ii) : i(ii) {}
    Egg(const Egg&);
public:
    static Egg* instance() {return &e;}
    int val() const {return i;}
};

Egg Egg::e(47);

int main()
{
    // Error -- can't create an Egg
    // You can access the single instance:
    // Egg x(1);
    cout << Egg::instance()->val() << endl;
}