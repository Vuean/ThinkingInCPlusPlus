#include <iostream>
using namespace std;

void TestFunction1(int first, int second)
{
    cout << "TestFunction1: " << endl;
}

void TestFunction2(int first, int)
{
    cout << "TestFunction2: " << endl;
}

int main()
{
    TestFunction1(1, 2);
    TestFunction2(1, 2);
}