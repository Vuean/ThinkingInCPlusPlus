// C03: IfElse.cpp
// Demonstration of if and if-else conditionals

#include<iostream>
using namespace std;

int main()
{
    int i;
    cout << "type a number and 'Enter'" << endl;
    cin >> i;

    if(i > 5)
        cout << "It's greater than 5" << endl;
    else if(i < 5)
        cout << "It's less than 5" << endl;
    else
        cout << "It's equal to 5" << endl;
    
    cout << "type a number and 'Enter'" << endl;
    cin >> i;
    if(i < 10)
    {
        if (i > 5)// "if" is just another statement
            cout << "5 < i < 10" << endl;
        else
            cout << "i <= 5" << endl;
    }
    else
        cout << "i >= 10" << endl;
    
    return 0;
}