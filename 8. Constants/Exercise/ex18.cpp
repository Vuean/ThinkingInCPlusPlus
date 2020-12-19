class X{};

X f()
{
    return X();
}

void g1(X&){}

void g2(const X&) {}

int main()
{
    // cannot bind non-const lvalue reference of type 'X&' to an rvalue of type 'X'
    // g1(f());
    g2(f());
}