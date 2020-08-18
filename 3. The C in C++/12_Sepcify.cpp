// C03:12_Specify.cpp
// Demonstrates the use of specifiers 

#include <iostream>
using namespace std;

int main()
{
    char c;
    unsigned char cu;
    int i;
    unsigned int iu;
    short int is;
    short iis;  // same as short int
    unsigned short int isu;
    unsigned short iisu;
    long int il;
    long iil;   // same as long int
    unsigned long int ilu;
    unsigned long iilu;
    float f;
    double d;
    long double ld;

    cout 
        << "\n char= " << sizeof(c)
        << "\n unsigned char= " << sizeof(cu)
        << "\n int= " << sizeof(i)
        << "\n unsigned int= " << sizeof(iu)
        << "\n short = " << sizeof(is)
        << "\n unsigned short= " << sizeof(isu)
        << "\n long = " << sizeof(il)
        << "\n unsigned long= " << sizeof(ilu)
        << "\n float = " << sizeof(f)
        << "\n double = " << sizeof(d)
        << "\n long double = " << sizeof(ld)
        << endl;
    return 0; 
}