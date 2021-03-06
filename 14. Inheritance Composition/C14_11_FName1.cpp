// C14_11_FName1.cpp
// An fstream with a file name
#include "../require.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class FName1
{
    ifstream file;
    string filename;
    bool named;
public:
    FName1() : named(false) {}
    FName1(const string& fname)
        : filename(fname), file(fname.c_str())
    {
        assure(file, filename);
        named = true;
    } 
    string name() const { return filename;}
    void name(const string& newName)
    {
        if(named) return;
        filename = newName;
        named = true;
    }
    operator ifstream&() {return file;}
};

int main()
{
    FName1 file("FName1.cpp");
    cout << file.name() << endl;
}

