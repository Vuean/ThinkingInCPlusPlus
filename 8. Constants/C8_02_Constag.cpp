// C08: Constag.cpp
// Constents and aggregates
const int i[] = {1, 2, 3, 4};

// ! float f[i[3]];     // Illegal
struct S
{
    int i, j;
};

const S s[] = {{1, 2}, {3, 4}};

// 错误，表达式必须含有常量值，尝试访问运行时存储
double d[s[1].j];    // Illegal

int main()
{}