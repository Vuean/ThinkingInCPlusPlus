// C06: Nojump.cpp
// Can't jump past constructors

class X
{
public:
    X();
};

X::X() {}

void f(int i)
{
    if (i < 10)
    {
        // !goto jumpl; // error: goto bypass init
    }
    X x1;   // Constructor called here
    jumpl:
    switch (i)
    {
        case 1: 
            X x2;
            break;
        case 2:
            X x3;
            break;
    }
}

int main()
{
    f(9);
    f(11);
}