// C02: Scopy.cpp
// Copy one fule to another, a line at a time

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main()
{
    ifstream in("07_Scopy.cpp");   // Open for reading
    ofstream out("07_Scopy2.cpp");  // Open for writing
    string s;
    while (getline(in, s))
        out << s << "\n";
    
    return 0;
}