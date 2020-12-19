#include <stdio.h>

const int a = 1, b = 2, c = 3;
char buf[a + b + c];

int main()
{
    printf("Size of buf is: %d\n", sizeof(buf));
    printf("Size of a is: %d\n", sizeof(a));
    printf("Address of b is: %p\n", &b);
}