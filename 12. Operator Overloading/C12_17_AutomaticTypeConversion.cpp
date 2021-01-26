// C12_17_AutomaticTypeConversion.cpp
// Type conversion constructor
class One
{
public:
    One() {}
};

class Two
{
public:
    Two(const One&) {}
};

void f(Two) {}

int main()
{
    One one;
    f(one); // Want a Two, has a One
}