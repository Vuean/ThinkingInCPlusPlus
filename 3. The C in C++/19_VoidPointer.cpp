// C03:19_VoidPointer.cpp

#include <iostream>
using namespace std;
int main()
{
    void* vp;
    char c;
    int i;
    float f;
    double d;
    // The address of ANY type can be assigned to a void pointer:
    vp = &c;
    vp = &i;
    vp = &f;
    vp = &d;
}