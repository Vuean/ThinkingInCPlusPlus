// C10_08_ScopeResolution.cpp
namespace X
{
    class Y
    {
        static int i;
    public:
        void f();
    };
    class Z;
    void func();
}

int X::Y::i = 9;
class X::Z
{
    int u, v, w;
public:
    Z(int i);
    int g();
};

X::Z::Z(int i)
{
    u = v = w = i;
}

int X::Z::g() {return u = v = w = 0;}


void Xfunc()
{
    X::Z a(1);
    a.g();
}

int main() {}