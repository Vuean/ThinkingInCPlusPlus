// C10_16_Statinit.cpp
// Scope of static initializer
#include <iostream>
using namespace std;

int x = 100;

class WithStatic{
    static int x;
    static int y;
public:
    void print() const
    {
        cout << "WithStatic::x = " << x << endl;
        cout << "WithStatic::y = " << y << endl;
    }
};

int WithStatic::x = 1;
int WithStatic::y = x + 1;

int main()
{
    WithStatic ws;
    ws.print();
}