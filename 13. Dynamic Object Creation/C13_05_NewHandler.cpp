// C13_05_NewHandler.cpp
// Changing the new-handler

#include <iostream>
#include <cstdlib>
#include <new>
using namespace std;

int Count = 0;

void out_of_memory()
{
    cerr << "memory exhausted after" << Count
         << " allocations!" << endl;
    exit(1);
}

int main()
{
    set_new_handler(out_of_memory);
    while(1)
    {
        Count++;
        new int[1000];
    }
}