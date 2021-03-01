// C13_06_GlobalOperatorNew.cpp
// Overload global new/operator

#include <cstdio>
#include <cstdlib>
using namespace std;

void* operator new(size_t sz)
{
    printf("operator new: %d Bytes\n", sz);
    void* m = malloc(sz);
    if(!m) puts("out of memory");
    return m;
}

void operator delete(void* m)
{
    puts("operator delete");
    free(m);
}

class S
{
    int i[100];
public:
    S() {puts("S::S()");}
    ~S() {puts("S::~S()");}
};

int main()
{
    puts("creating & destorying an int");
    int* p = new int(47);
    delete p;
    puts("creating destorying an s");
    S* s = new S;
    delete s;
    puts("creating & destorying S[3]");
    S* sa = new S[3];
    delete []sa;
}