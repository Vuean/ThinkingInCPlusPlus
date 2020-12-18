// C8_11_EncapsulatingTypes.cpp
#include <iostream>
using namespace std;

class IntegerTest
{
    int i;
public:
    IntegerTest(int ii = 0);
    void print();
};

IntegerTest::IntegerTest(int ii) : i(ii) {}

void IntegerTest::print()
{
    cout << i << ' ';
}

int main()
{
    IntegerTest i[10];
    for(int j = 0; j < 10; ++j)
        i[j].print();
}
