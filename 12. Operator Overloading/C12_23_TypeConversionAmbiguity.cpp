// C12_23_TypeConversionAmbiguity.cpp
class Orange;   // Class declaration

class Apple
{
public:
    operator Orange() const;    // Convert Apple to Orange
};

class Orange
{
public:
    Orange(Apple);  // Convert Apple to Orange
};

void f(Orange) {}

int main()
{
    Apple a;
    // 应用多个用户定义的从 "Apple" 到 "Orange" 的转换
    // f(a);   // Error: ambiguous conversion
}