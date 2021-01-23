// C12_16_AutomaticOperatorEqual.cpp
#include <iostream>
using namespace std;
class Cargo
{
public:
    Cargo& operator=(const Cargo&)
    {
        cout << "inside Cargo::operator=()" << endl;
        return *this;
    }
};

class Truck
{
    Cargo n;
};

int main()
{
    Truck a, b;
    a = b;
}