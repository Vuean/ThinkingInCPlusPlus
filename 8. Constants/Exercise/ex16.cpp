void t(int*) {}

void u(const int* cip)
{
    // 表达式必须是可修改的左值
    // *cip = 2;
    int i = *cip;
    // "const int *" 类型的值不能用于初始化 "int *" 类型的实体
    // int* ip2 = cip;
}