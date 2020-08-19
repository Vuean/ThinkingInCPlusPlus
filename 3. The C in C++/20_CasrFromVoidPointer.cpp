// C03:20_CasrFromVoidPointer.cpp

int main()
{
    int i = 99;
    void* vp = &i;
    // Can't dereference(½â³ıÒıÓÃ) a void pointer:
    // *vp = 3; // compile-time error
    // Must cast back to int before dereferencing:
    *((int*)vp) = 3;
    return 0;
}