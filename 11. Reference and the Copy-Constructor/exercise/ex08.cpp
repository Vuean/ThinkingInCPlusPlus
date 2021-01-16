#include <iostream>
using namespace std;

void func(char& c)
{
    c = 'C';
}

int main()
{
    char input = 'a';
    cout << "input: " << input << endl;
    func(input);
    cout << "input = " << input << endl;
}