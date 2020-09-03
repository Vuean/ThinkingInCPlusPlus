#include <iostream>
using namespace std;

int main()
{
    string s[5];
    for (int i = 0; i < 5; ++i)
    {
        cout << "Enter string: ";
        cin >> s[i];
    }

    cout << "Output the string array: " << endl;
    for (int i = 0; i < 5; ++i)
        cout << s[i] << " ";
    cout << endl;
    return 0;
}