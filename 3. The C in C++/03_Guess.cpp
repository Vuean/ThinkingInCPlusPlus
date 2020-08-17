// C03: 03_Guess.cpp
// Guess a number (demonstrates "while")

#include <iostream>
using namespace std;

int main()
{
    int secret = 15;
    int guess = 0;
    while( guess != secret ){
        cout << "guess the number: ";
        cin >> guess;
    }
    cout << "You guessed it!" << endl;
    return 0;
}