class Z 
{
	int i;
	mutable int j;
public:
	Z();
	void f() const;
};

Z::Z() : i(0), j(0) {}

void Z::f() const 
{
    // i++;
    j++;
}

int main()
{
    const Z z1;
    z1.f();
}