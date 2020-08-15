// C02: HelloStrings.cpp
// The basics of the Standard C++ string class

#include <string>
#include <iostream>
using namespace std;

int main()
{
    string s1, s2;  // Empty strings
    string s3 = "hello world!";  // Initialized
    string s4("I am");// Initialized
    s2 = "Today";   // assigning to a string
    s1 = s3 + " " + s4; //combinging strings
    s1 += " tense ";
    cout << s1 + s2 + "!" << endl;
    return 0;
}