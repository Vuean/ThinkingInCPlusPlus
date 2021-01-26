// C12_25_TypeConversionFanout2.cpp
class Fi {};

class Fee
{
public:
    Fee(int){}
    Fee(const Fi&) {}
};

class Fo
{
    int i;
public:
    Fo(int x = 0) : i(x) {}
    operator Fee() const {return Fee(i);}
};

int main()
{
    Fo fo;
    Fee fee = fo;
}