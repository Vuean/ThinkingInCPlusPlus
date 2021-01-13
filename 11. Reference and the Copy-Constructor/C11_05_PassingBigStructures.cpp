// C11_05_PassingBigStructures.cpp
struct Big
{
    char buf[100];
    int i;
    long d;
}B, B2;

Big bigfun(Big b)
{
    b.i = 100;
    return b;
}

int main()
{
    B2 = bigfun(B);
}