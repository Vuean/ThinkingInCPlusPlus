// C02: IntVector.cpp
// Creating a vector that holds integers

#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> v;
    for(int i = 0; i < 10; i++)
        v.push_back(i);

    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << ", ";
    }
    cout << endl;

    for (int i = 0; i < v.size(); i++)
    {
        v[i] = v[i] * 10;
    }
    
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << ", ";
    }
    cout << endl;
    return 0;
}