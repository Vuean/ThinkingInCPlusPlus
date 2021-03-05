// C14_05_PseudoConstructor.cpp
class X
{
    int i;
    float f;
    char c;
    char* s;
public:
    X() : i(7), f(1.4), c('x'), s("howdy") {}
};

int main()
{
    X x;
    int i(100);
    int *ip = new int(47);
}