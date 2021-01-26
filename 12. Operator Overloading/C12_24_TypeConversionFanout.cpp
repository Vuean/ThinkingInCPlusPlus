// C12_24_TypeConversionFanout.cpp
class Orange {};
class Pear {};

class Apple 
{
public:
    operator Orange() const;
    operator Pear() const;
};

// Overloaded eat();
void eat(Orange);
void eat(Pear);

int main()
{
    Apple(c);
    // 有多个 重载函数 "eat" 实例与参数列表匹配:
    // eat(c); // Error: Apple->Orange or Apple->Pear？？？
}