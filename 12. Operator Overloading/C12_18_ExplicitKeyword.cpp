// C12_18_ExplicitKeyword.cpp
// Using the "explicit" keyword
class One
{
public:
    One(){}
};

class Two
{
public:
    explicit Two(const One&){}
};

void f(Two) {}

int main()
{
    One one;
    // f(one); // No auto conversion allowed
    f(Two(one));
}