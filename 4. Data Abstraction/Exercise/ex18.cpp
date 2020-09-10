#include <iostream>
#include <string>
using namespace std;

char* func1(char* stringtocopy)
{
    int stringlength = strlen(stringtocopy);
    char* stringtoreturn = new char[stringlength + 1];
    for(int i = 0; i < stringlength; i++)
        stringtoreturn[i] = stringtocopy[i];
    stringtoreturn[stringlength] = '\0';
    return stringtoreturn;
}

int main()
{
    char* ch_array1 = func1("hello C++");
    char* ch_array2 = func1(ch_array1);

    cout << "String 1: " << ch_array1 << endl;
    cout << "Address of 1st string: " << (long long)static_cast<void*>(ch_array1) << endl;
    cout << "String 2: " << ch_array2 << endl;
    cout << "Address of 2nd string: " << (long long)static_cast<void*>(ch_array2) << endl;

    delete[] ch_array1;
    delete[] ch_array2;
}