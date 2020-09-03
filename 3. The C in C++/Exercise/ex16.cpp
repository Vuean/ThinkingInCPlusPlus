#include <iostream>
using namespace std;

enum COLOR{
    RED,
    BLUE,
    GREEN,
    YELLOW,
    PINK,
    BLACK,
    WHITE
};

int main()
{
    for(COLOR myColor = RED; myColor <= WHITE; myColor = static_cast<COLOR>(myColor + 1))
        cout << myColor << endl;
}