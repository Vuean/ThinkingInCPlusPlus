// C8_15_Castway.cpp
// "Casting away" constness

class Y
{
    int i;
public:
    Y();
    void f() const;
};

Y::Y() {i = 0;}

void Y::f() const
{
    // 表达式必须是可修改的左值
    // i++; // Error -- const member function
    ((Y*)this)->i++;    // OK -- cast away const-ness
    // Better: use C++ explicit casr syntax
    (const_cast<Y*>(this))->i++; // OK
}

int main() 
{
    const Y yy;
    yy.f();// Actually changes it!
}