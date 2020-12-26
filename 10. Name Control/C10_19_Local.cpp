// C10_19_Local.cpp
// Static members & local classes
#include <iostream>
using namespace std;

// Mested class CAN have static data members:
class Outer
{
    class Inner{
        static int i;   // ok
    };
};

int Outer::Inner::i = 47;

// Local class cannot have static data members:
void f()
{
    class Local{
    public:
        // static int i;    // Error
    } x;
}
int main() { Outer x; f();}