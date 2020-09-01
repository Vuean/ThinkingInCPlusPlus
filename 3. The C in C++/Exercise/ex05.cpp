#include <iostream>
using namespace std;

int main()
{
    int X, Y, Z;
    cout << "Enter X: "; cin >> X;
    cout << "Enter Y: "; cin >> Y;
    cout << "Enter Z: "; cin >> Z;

    cout << "Result for first expression: " << X + Y -2 / 2 + Z << endl;
    cout << "Result for second expression: " << X + (Y - 2) / (2 + Z) << endl;
}