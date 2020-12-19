int d = 1;
const int e = 2;
int* u = &d;

// "const int*"类型的值不能用于初始化"int*"类型的实体
// int* v = &e;

// 直接强制类型转换
int* w = (int*)(&e);