#include <iostream>
using namespace std;

class First
{
    int x;
    friend const First operator+(const First& left, const First& right);
public:
    First(int xx = 0) : x(xx) {} 
};

class Second
{
    int y;
public:
    explicit Second(int yy = 0) : y(yy) {}
    operator First() const
    { 
        cout << "operator First() called." << endl;
        return First(y);
    }
};

const First operator+(const First& left, const First& right)
{
    return First(left.x + right.x);
}

int main()
{
    First f;
    Second s;

    f + 1;
    2 + f;

    s + 3;
    4 + s;

    f + s;
    s + f;
}
