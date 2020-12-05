#include <iostream>
#include "..\C6_07_Stack3.h"
using namespace std;

int main()
{
    string s1[] = {"name", "age", "sex", "weight"};
    Stack stack1;

    for(int i = 0; i < (sizeof(s1)/sizeof(*s1)); i++)
    {
        stack1.push(&s1[i]);
    }
    string* line;
    while((line = (string*)stack1.pop()) != 0)
        cout << *line << endl;
}