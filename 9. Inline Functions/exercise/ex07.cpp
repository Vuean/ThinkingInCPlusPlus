#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
using namespace std;

class X
{
    char* array_test;
    int length;
public:
    X(const int _length, const int init = '-')
    {
        this->length = _length;
        array_test = new char[length];
        memset(array_test, init, sizeof(char) * length);
    }
    ~X()
    {
        delete [] array_test;
    }
    inline void print()
    {
        for(int i = 0; i < length; i++)
            cout << array_test[i] << " ";
        cout << endl;
    }
};

int main()
{
    X x(10, 'A');
    x.print();
}