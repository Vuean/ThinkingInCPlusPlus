#include <iostream>
using namespace std;

int dog;
float cat;
double bird;
char fish;
long long cow;

void f(int pet)
{
    cout << "pet id number: " << pet << endl;
}

int main()
{
    int i;
    double j;
    float k;

    cout << "f(): " << (long long)&f << endl;
    cout << "dog: " << (long long)&dog << endl;
    cout << "cat: " << (long long)&cat << endl;
    cout << "bird: " << (long long)&bird << endl;
    cout << "fish: " << (long long)&fish << endl;
    cout << "i: " << (long long)&i << endl;
    cout << "j: " << (long long)&j << endl;
    cout << "k: " << (long long)&k << endl;
    return 0;
}
