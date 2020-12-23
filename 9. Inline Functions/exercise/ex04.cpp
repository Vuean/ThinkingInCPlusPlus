#include <iostream>
#include <ctime>
using namespace std;

static const int ARRAY_SIZE = 100000000;
int int_array[ARRAY_SIZE];

void f1()
{
    for(int i = 0; i < ARRAY_SIZE; i++)
        int_array[i] = i;
}

inline void f2()
{
    for(int i = 0; i < ARRAY_SIZE; i++)
        int_array[i] = i;
}

int main()
{
    clock_t start_f1 = clock();
    f1();
    clock_t end_f1 = clock();
    cout << "f1() time: " << (double)(end_f1 - start_f1)/CLOCKS_PER_SEC << endl;

    clock_t start_f2 = clock();
    f2();
    clock_t end_f2 = clock();
    cout << "f2() time: " << (double)(end_f2 - start_f2)/CLOCKS_PER_SEC << endl;
}