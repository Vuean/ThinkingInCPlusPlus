#include <iostream>
using namespace std;

class test
{
public:
    test(){};
    virtual ~test(){};
};

int main()
{
    // test& tr1;  // ±ØĞë³õÊ¼»¯
    test t1;
    test t2;
    test& tr = t1;

    tr = t2;
    // int& tr2 = NULL;
}