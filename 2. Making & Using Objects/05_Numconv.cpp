// C02: Numconv.cpp
// 将十进制转换为八进制和十六进制

#include <iostream>
using namespace std;

int main()
{
    int number;
    cout << "Enter a decimal number: ";
    cin >> number;

    cout << "value in octal = 0"
         << oct << number << endl;
    cout << "value in hex = 0x"
         << hex << number << endl;
    
    return 0;
}