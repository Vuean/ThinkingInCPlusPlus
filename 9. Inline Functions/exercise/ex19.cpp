#include <iostream>
using namespace std;

#define FIELD(index) private: int int_##index; \
    public: int integer_##index() {return int_##index;} \
    void integer_##index(int value) {int_##index = value;}

class X
{
    FIELD(1);
    FIELD(2);
    FIELD(3);
};

int main()
{
    X x;
    x.integer_1(1);
    x.integer_2(2);
    x.integer_3(3);

    cout << x.integer_1() << endl;
    cout << x.integer_2() << endl;
    cout << x.integer_3() << endl;
}