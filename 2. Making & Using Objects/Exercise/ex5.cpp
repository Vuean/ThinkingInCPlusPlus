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
    while(in >> word)
        words.push_back(word);

    for (int i = words.size()-1; i > 0; --i)
        cout << i << ": " << words[i] << endl;
    return 0;
}