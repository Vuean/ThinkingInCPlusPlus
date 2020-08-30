// C03:45_DynamicDebugFlags.cpp
#include <iostream>
#include <string>
using namespace std;

// Debug flags aren't necessaruly global:
bool debug = false;

int main(int argc, char* argv[])
{
    for (int i = 1; i < argc; ++i)
        if(string(argv[i]) == "--debug=on")
            debug = true;
    bool go = true;
    while (go){
        if (debug){
            // Debugging code here
            cout << "Debugger is now on!" << endl;
        }
        else{
            cout << "Debugger is now off!" << endl;
        }
        cout << "Turn Debugger [on/off/quit]: ";
        string reply;
        cin >> reply;
        if(reply == "on") debug = true; // Turn it on
        if(reply == "off") debug = false; // Turn it off
        if(reply == "quit") break; // Out of 'while'
    }
}