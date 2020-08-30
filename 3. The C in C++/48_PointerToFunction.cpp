// C03:48_PointerToFunction.cpp
// Defining and using a pointer to a function
#include <iostream>
using namespace std;

void func(){
    cout << "func() called..." << endl;
}

int main()
{
    void (*fp)();   // Define a function pointer
    fp = func;  // Initialize it
    (*fp)();    // Dereferencing(接触指针的关联) calls the function
    void (*fp2)() = func; // Define and initialize
    (*fp2)(); 
}