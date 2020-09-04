// C04: C4_04_Sizeof.cpp
// sizeof struct
#include <iostream>
#include "C4_01_Clib.h"
#include "C4_03_CPPLib.h"
using namespace std;

struct A{
    char c;
    int i[100]; // 单独一个数组时是400字节
};

struct B{
    void f();
};

void B::f() {}

int main()
{
    cout << "sizeof struct A = " << sizeof(A) << " bytes." << endl;
    cout << "sizeof struct B = " << sizeof(B) << " bytes." << endl;
    cout << "sizeof CStash in C = " << sizeof(CStash) << " bytes." << endl;
    cout << "sizeof CStash in C++ = " << sizeof(Stash) << " bytes." << endl;
    return 0;
}