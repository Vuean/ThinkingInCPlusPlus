// C6: Stash2Test.cpp
#include "C6_04_Stash2.h"
#include "../require.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    Stash intStash(sizeof(int));
    for(int i = 0; i < 100; ++i)
        intStash.add(&i);
    for(int j = 0; j < intStash.count(); ++j)
        cout << "intStash.fetch(" << j << ") = "
             << *(int*) intStash.fetch(j)
             << endl;
    const int bufsize = 80;
    Stash stringStash(sizeof(char) * bufsize);
    ifstream in("C6_06_Stash2Test.cpp");
    assure(in, " C6_06_Stash2Test.cpp");
    string line;
    while(getline(in, line))
    {
        stringStash.add((char*)line.c_str());
    }
    int k = 0;
    char* cp;
    while((cp = (char*)stringStash.fetch(k++)) != 0)
        cout << "stringStach.fetch(" << k << ") = " << cp << endl;
}