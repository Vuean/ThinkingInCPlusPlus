// C12_07_OverloadingOperatorComma.cpp
#include <iostream>
using namespace std;

class After
{
public:
    const After& operator,(const After&) const
    {
        cout << "After::operator,()" << endl;
        return *this;
    }
};

class Before {};

Before& operator,(int, Before& b)
{
    cout << "Before::operator,()" << endl;
    return b;
}

int main()
{
    After a, b;
    a, b;   // Operator comma, called

    Before c;
    1, c;
}