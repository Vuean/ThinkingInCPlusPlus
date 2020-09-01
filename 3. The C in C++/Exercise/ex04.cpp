#include <iostream>
using namespace std;

int main()
{
    char c;
    while(c != 'q'){
        cout << "Main Menu: " << endl;
        cout << "l: left, r: right, q: quit -> ";
        cin >> c;
        switch(static_cast<int>(c)){
            case 113:
                break;
            case 108:{
                cout << "LEFT MENU: " << endl;
                cout << "select a or b: ";
                cin >> c;
                switch(static_cast<int>(c)){
                    case 97:{
                        cout << "you choose 'a'" << endl;
                        break;
                    }
                    case 98:{
                        cout << "you choose 'b'" << endl;
                        break;
                    }
                    default:{
                        cout << "you didn't choose a or b" << endl;
                        break;
                    }
                }
                break;
            }
            case 114:{
                cout << "RIGHT MENU: " << endl;
                cout << "select c or d: ";
                cin >> c;
                switch(static_cast<int>(c)){
                    case 99:{
                        cout << "you choose 'c'" << endl;
                        break;
                    }
                    case 100:{
                        cout << "you choose 'd'" << endl;
                        break;
                    }
                    default:{
                        cout << "you didn't choose c or d" << endl;
                        break;
                    }
                }
                cout << "you must type l or r or q!" << endl;
                break;
            }
        }
    }
    cout << "quitting menu..." << endl;
}