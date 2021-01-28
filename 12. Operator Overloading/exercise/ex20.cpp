#include <iostream>
using namespace std;

class Test
{
    int x;
public:
    Test(int xx = 0) : x(xx) {}
};

// “operator=”必须是成员函数
const Test& operator=(const Test& left, const Test& right)
{
    if(&left == &right)
        return left;
    left.x = right.x;
    return left;
}

int main()
{

}