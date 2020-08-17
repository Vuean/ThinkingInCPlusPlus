// C03: 05_Charlist.cpp
// Display all the ASCII characters

#include <iostream>
using namespace std;

int main()
{
    for(int i = 0; i < 128; i++)
    {
        if(i != 26) // ANSI Terminal Clear screen
            cout << "value: " << i << " characters "
                 << char(i) // Type conversion
                 << endl;
    }
    return 0;
}