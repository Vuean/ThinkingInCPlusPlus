// C8_05_ConstVal.cpp
// Returing consts by value
// has not meaning for built-in types
#include <iostream>
using namespace std;

int f3()    { return 1;}
const int f4() { return 1;}

int main()
{
    const int j = f3(); // works fine
    int k = f4(); // This works fine too!
    cout << "j = " << j << endl;
    cout << "k = " << k << endl;
}