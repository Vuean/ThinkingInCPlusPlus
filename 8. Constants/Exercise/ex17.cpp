void t(int&) {}

void u(const int& cip)
{
    // 表达式必须是可修改的左值
    // *cip = 2;
    int i = cip;
    // "const int *" 类型的值不能用于初始化 "int *" 类型的实体
    // int* ip2 = cip;
}

const char& v()
{
    return *"result of function v()";
}

const int& w()
{
    static int i;
    return i;
}

int main()
{
    int x = 0;
    int& ip = x;
    const int& cip = x;
    t(ip);
    // t(cip);
    u(ip);
    u(cip);
    //! char& cp = v();	
	const char& ccp = v();
    //	int& ip2 = w();	
	const int& ccip = w();
	const int& cip2 = w();
    //	*w() = 1;	
}