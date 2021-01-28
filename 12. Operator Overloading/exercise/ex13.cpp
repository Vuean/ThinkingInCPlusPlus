#include <iostream>
using namespace std;

class PointerClass
{
    int* iPtr;
public:
    PointerClass() : iPtr(new int) {}
    void showAddress() const { cout << "Pointer: " << iPtr << endl; }
    
    // opearator=
    // PointerClass& operator=(const PointerClass& right)
    // {
    //     if(this == &right)
    //         return *this;
    //     iPtr = new int(*right.iPtr);
    //     return *this;
    // }
};

int main()
{
    PointerClass a, b;
    a = b;
    a.showAddress();
    b.showAddress();
}