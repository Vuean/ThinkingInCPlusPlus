#define CPPSTYLE

# ifdef CPPSTYLE
#include <iostream>
using namespace std;
#endif

#ifdef CSTYLE
#include <stdio.h>
#endif

int main()
{
    #ifdef CPPSTYLE
        cout << "Some message by CPP style..." << endl;
    #endif
    #ifdef CSTYLE
        printf("Some message by C style...\n");
    #endif
}