// C02: FillVector.cpp
// Copy an entire file into a vector of string

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
    vector<string> v;
    ifstream in("09_FillVector.cpp");
    string line;
    while(getline(in, line))
        v.push_back(line);  // Add the line to the end
    for (int i = 0; i < v.size(); i++)
    {
        cout << i << ": " << v[i] << endl;
    }
    return 0;    
}