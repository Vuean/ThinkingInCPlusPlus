#include <iostream>
using namespace std;

int main()
{
    int* i_ptr = new int;
    long* l_ptr = new long;
    char* c_array = new char[100];
    float* f_array = new float[10];

    cout << "Address i_ptr: " << static_cast<void*>(i_ptr) << endl;
    cout << "Address l_ptr: " << static_cast<void*>(l_ptr) << endl;

    for(int i = 0; i < 100; i++)
        cout << "Address c_array[" << i << "] = " << static_cast<void*>(&c_array[i]) << endl;
    
    for (int i = 0; i < 10; i++)
        cout << "Address f_array[" << i << "] = " << static_cast<void*>(&f_array[i]) << endl;
    
    delete i_ptr;
    delete l_ptr;
    delete[] c_array;
    delete[] f_array;
}