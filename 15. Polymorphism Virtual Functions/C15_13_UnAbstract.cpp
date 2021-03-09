// C15_13_UnAbstract.cpp
// Pure virtual destructors seem to behave strangely

class AbstractBase
{
public:
    virtual ~AbstractBase() = 0;
};

AbstractBase::~AbstractBase() {}

class Derived : public AbstractBase {};
// No overloading of destructor necessary?
int main()
{
    Derived d;
}