// C03: 39_StructArray.cpp
// An array of struct

typedef struct {
    int i, j, k;
}ThreeDPoint;

int main()
{
    ThreeDPoint p[10];
    for(int i = 0; i < 10; i++)
    {
        p[i].i = i + 1;
        p[i].j = i + 2;
        p[i].k = i + 3;
    }
}