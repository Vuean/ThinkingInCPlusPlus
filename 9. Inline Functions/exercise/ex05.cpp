#include <iostream>
#include <ctime>
using namespace std;

static const int ARRAY_SIZE = 200000000;
int int_array[ARRAY_SIZE];

int f1(int a, int b)
{
    return a + b;
}

inline int f2(int a, int b)
{
    return a + b;
}

int main()
{
    clock_t start_f1 = clock();
    for(int i = 0; i < ARRAY_SIZE; i++)
        int_array[i] = f1(i, i+1);
    clock_t end_f1 = clock();
    cout << "f1() time: " << (double)(end_f1 - start_f1)/CLOCKS_PER_SEC << endl;

    clock_t start_f2 = clock();
    for(int i = 0; i < ARRAY_SIZE; i++)
        int_array[i] = f2(i, i+1);
    clock_t end_f2 = clock();
    cout << "f2() time: " << (double)(end_f2 - start_f2)/CLOCKS_PER_SEC << endl;
}