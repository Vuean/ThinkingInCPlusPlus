// C07:AnonymousUnion.cpp
int main()
{
    union{
        int i;
        float f;
    };
    // Acess members without using quantities
    i = 12;
    f = 1.22;
}