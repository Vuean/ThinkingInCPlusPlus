#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    vector<string> words;
    ifstream in("ex5.txt");
    string word;

    while (in >> word)
        words.push_back(word);
    
    string full;

    for (int i = 0; i < words.size(); i++)
        full += words[i] + " ";
    
    cout << full << endl;

    return 0;
}