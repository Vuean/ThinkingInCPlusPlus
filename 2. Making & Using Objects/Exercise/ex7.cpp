#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    fstream in("ex5.txt");

    string line;
    int tmp;

    while(getline(in, line))
    {
        cout << line << endl;
        cin.ignore();
    }

    return 0;
}