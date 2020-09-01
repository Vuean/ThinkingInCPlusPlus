#include <iostream>
using namespace std;

int main()
{
    string s1;
    cout << "Enter a word: " << endl;
    while(cin >> s1){
        int a = s1.size();
        if(a < 5){
            cout << "The size of the word is less than 5." << endl;
            cout << "Break;" << endl;
            break;
        }

        switch(a){
            case 5:
                cout << "The size of the word is 5." << endl;
                break;
            case 6:
                cout << "The size of the word is 6." << endl;
                break;
            case 7:
                cout << "The size of the word is 7." << endl;
                break;
            default:
                cout << "The size of the word is larger than 7." << endl;
                break;
        }
        
        cout << "Enter a word: " << endl;
    }
}