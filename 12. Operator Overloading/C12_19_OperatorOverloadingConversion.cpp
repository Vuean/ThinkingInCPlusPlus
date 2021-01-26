// C12_19_OperatorOverloadingConversion.cpp
class Three
{
    int i;
public:
    Three(int ii = 0, int = 0) : i(ii) {}
};

class Four
{
    int x;
public:
    Four(int xx) : x(xx) {}
    operator Three() const { return Three(x);}
};

void g(Three){}

int main()
{
    Four four(1);
    g(four);
    g(1);   // Calls Three(1, 0)
}