// C03:28_Boolean.cpp
// Relationship and operators

#include <iostream>
using namespace std;

int main()
{
    int i, j;
    cout << "Enter an integer: ";
    cin >> i;
    cout << "Enter another integer: ";
    cin >> j;
    cout << "i > j is " << (i > j) << endl;
    cout << "i < j is " << (i < j) << endl;
    cout << "i >= j is " << (i >= j) << endl;
    cout << "i <= j is " << (i <= j) << endl;
    cout << "i == j is " << (i == j) << endl;
    cout << "i != j is " << (i != j) << endl;
    cout << "i && j is " << (i && j) << endl;
    cout << "i || j is " << (i || j) << endl;
    cout << "(i < 10) && (j < 10) is " << ((i < 10) && (j < 10)) << endl;
    return 0;
}