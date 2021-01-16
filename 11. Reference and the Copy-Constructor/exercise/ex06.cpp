#include <iostream>
using namespace std;
void increment(int*& i) {i++;}

int main()
{
    int* i = 0;
    cout << "i = " << i << endl;
    increment(i);
    cout << "i = " << i << endl;
}