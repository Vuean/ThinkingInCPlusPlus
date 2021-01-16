#include <iostream>
using namespace std;

int increment(int x) 
{
    x++;
    return x;
}

int main() 
{
    int y = 10;
    increment(y);
    return 0;
}