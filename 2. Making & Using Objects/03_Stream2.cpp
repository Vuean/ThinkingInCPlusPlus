// C02: Stream2.cpp
// More streams features

#include <iostream>
using namespace std;

int main()
{
    // 用操作器指定格式
    cout << "a number in decimal: " 
         << dec << 15 << endl;
    cout << "a number in octal: " 
         << oct << 15 << endl;
    cout << "a number in hex: " 
         << hex << 15 << endl;
    cout << "a floating-point number: " 
         << 3.1415926 << endl;
    cout << "non-printing char (escape): "
         << char(27) << endl;
    return 0;
}