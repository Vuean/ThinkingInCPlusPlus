#include <iostream>
using namespace std;

void printArray(double* array, int array_size)
{
    for (int i = 0; i < array_size; i++)
        cout << array[i] << " ";
    cout << endl;
}

int main()
{
    double d[] = {0, 0, 0, 0, 0, 0};
    printArray(d, 6);

    unsigned char* uchar_ptr = reinterpret_cast<unsigned char*>(d);
    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < sizeof(double); j++)
        {
            uchar_ptr[i*sizeof(double)+j] = 1;
        }
    }
    printArray(d, 6);
}