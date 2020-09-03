#include <iostream>
using namespace std;

int main()
{
    float f1;
    float* fp = &f1;
    unsigned char* c;
    c = reinterpret_cast<unsigned char*>(fp);
    cout << "Enter float value: "; cin >> f1;
    for(int i = 0; i < sizeof(float); i++, c++)
    {
        cout << *c;
        cout << " ";
    }
}