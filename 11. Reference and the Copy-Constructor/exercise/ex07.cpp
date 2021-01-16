#include <iostream>
using namespace std;

void func(int**& refpptr)
{
    (*refpptr) += 1;
}

int main()
{
    int int_array[] = {1, 2, 3};
    int* iPtr = int_array;   // ptr to array's head
    int** iPtrPtr = &iPtr;  // ptr to ptr to array's head
    cout << *(*iPtrPtr) << endl;
    func(iPtrPtr);
    cout << *(*iPtrPtr) << endl; 
}