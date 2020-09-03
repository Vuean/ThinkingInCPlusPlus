#include <iostream>
#include <cassert>
using namespace std;

// A macro to define dummy functions:
#define DF(N) string N() {\
    assert("a" != #N); return #N;}

DF(a); DF(b); DF(c); DF(d); DF(e); DF(f); DF(g);

string (*func_table[])() = { a, b, c, d, e, f, g};

int main()
{
    string var;
    while(1){
        cout << "press a key from 'a' to 'g' " "or q to quit" << endl;
        char c, cr;
        cin.get(c); cin.get(cr);
        if(c == 'q')
            break;
        if(c < 'a' || c > 'g')
            continue;
        var = (*func_table[c - 'a'])(); 
        cout << "function " << var << " called..." << endl;
    }
}