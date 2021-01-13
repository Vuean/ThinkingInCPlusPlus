// C11_03_ConstReferenceArguments.cpp

// Passing references as const
void f(int&){}
void g(const int&) {}
int main()
{
    // f(1);   // Error
    g(1);
}