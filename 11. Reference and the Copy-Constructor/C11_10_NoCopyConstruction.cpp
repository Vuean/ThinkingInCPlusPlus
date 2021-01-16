//C11_10_NoCopyConstruction.cpp
// Preventing copy-construction
class NoCC
{
    int i;
    NoCC(const NoCC&);  // No definition
public:
    NoCC(int ii = 0) : i(ii) {}
};

void f(NoCC);

int main()
{
    NoCC n;
    // f(n); // Error: copy-constructor called
    // NoCC n2 = n;
    // NoCC n3(n);
}