// C11_02_Reference.cpp

int* f(int* x)
{
    (*x)++;
    return x;   // safe, x is outside this scope
}

int& g(int& x)
{
    x++;
    return x;   // safe, outside this scope
}

int& h()
{
    int q;
    // return q; // Error
    static int x;
    return x; // Safe, x lives outside this scope
}

int main()
{
    int a = 0;
    f(&a);
    g(a);
}