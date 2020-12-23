#include <iostream>
using namespace std;

enum Hue{
    red,
    blue,
    yellow
};

class Color
{
    Hue h;
public:
    Color() : h() {}
    Color(Hue _h) : h(_h) {}
    inline Hue getHue() { return h; }
    inline void setHue(Hue _h) { this->h = _h; }
    inline void print()
    {
        switch(this->getHue())
        {
            case red:
                cout << "red" << endl;
                break;
            case blue:
                cout << "blue" << endl;
                break;
            case yellow:
                cout << "yellow" << endl;
                break;
            default:
                cout << "unknown" << endl;
                break;
        }
    }
};

int main()
{
    Color c1;
    Hue h2 = blue;
    Color c2(h2);
    c1.print();
    c2.print();
}