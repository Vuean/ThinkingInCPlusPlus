#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    int count = 0;
    
    fstream in("ex5.txt");
    string word;
    string match = "C++";
    while (in >> word)
    {
        if(word == match)
            count++;
    }
    cout << "The word: \"" << match << "\" occurred " << count << " times!" << endl;

    return 0; 
}