// C03: 36_SimpleStruct1.cpp
// Using pointers to structs
typedef struct Structre3{
    char c;
    int i;
    float f;
    double d;
} Structre3;

int main()
{
    Structre3 s1, s2;
    Structre3* sp = &s1;
    sp->c = 'a'; // Select an element using a '.'
    sp->i = 1;
    sp->f = 3.14;
    sp->d = 0.00093;
    sp = &s2;      // Point to a different struct object
    sp->c = 'a';
    sp->i = 1;
    sp->f = 3.14;
    sp->d = 0.00093;
}