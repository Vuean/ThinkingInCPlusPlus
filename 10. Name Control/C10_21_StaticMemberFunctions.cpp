// C10_21_StaticMemberFunctions.cpp
class X
{
    int i;
    static int j;
public:
    X(int ii = 0) : i(ii)
    {
        // Non-static member function can access
        // static member function or data:
        j = i;
    }
    int val() const { return i; }
    static int incr()
    {
        // i++; // Error: static member function
        // cannot access non-static member data
        return ++j;
    }
    static int f()
    {
        // 静态成员必须于特性对象相对
        // Error: static member function cannot access 
        // non-static member function
        // val();
        return incr();
    }
};

int X::j = 0;
int main()
{
    X x;
    X* xp = &x;
    x.f();
    xp->f();
    X::f(); // Only works with static members`
}