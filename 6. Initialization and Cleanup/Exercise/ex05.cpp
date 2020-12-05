#include <iostream>
using namespace std;

int main()
{
    cout << "Part one: " << endl;
    int i = 0;
    for(; i < 5; i++)
    {
        cout << i << " ";
    }
    cout << endl;
    for(int j = 0; j < 6; j++)
    {
        cout << j << " ";
    }
    cout << endl;

    cout << "Part two: " << endl;
    for(int i = i, j = 0; j < 6; j++)
    {
        cout << i << " ";
    }
    cout << endl;
}