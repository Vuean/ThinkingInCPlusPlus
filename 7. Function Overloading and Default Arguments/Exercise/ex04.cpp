#include <iostream>
using namespace std;

class AClass
{
    int value1, value2, value3, value4;
public:
    AClass();
    void SetValue(int = 1, int = 2, int = 3, int = 4);
};

AClass::AClass()
{
    value1 = value2 = value3 = value4 = 0;
}

void AClass::SetValue(int value1, int value2, int value3, int value4)
{
    this->value1 = value1;
    this->value2 = value2;
    this->value3 = value3;
    this->value4 = value4;
    cout << value1 << " " << value2 << " " << value3 << " " << value4 << endl;
}

int main()
{
    AClass theClass;
    theClass.SetValue(1);
    theClass.SetValue(1, 2);
    theClass.SetValue(1, 2, 3);
    theClass.SetValue(1, 2, 3, 4);
}