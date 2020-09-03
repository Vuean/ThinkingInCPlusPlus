#include <iostream>
#include <string>
using namespace std;

typedef struct Ex15{
    string Name;
    string Address;
    int Age;
} Ex15;

int main()
{
    Ex15 Stu1;
    Ex15* Stu2;

    Stu1.Name = "Baidu";
    Stu1.Address = "Beijing";
    Stu1.Age = 30;

    cout << "Student Stu1's card is following: " << endl;
    cout << Stu1.Name << endl;
    cout << Stu1.Address << endl;
    cout << Stu1.Age << endl;

    Stu2 = &Stu1;
    Stu2->Name = "Kuaishou";
    Stu2->Address = "XiErQi";
    Stu2->Age = 10;

    cout << "Student Stu2's card is following: " << endl;
    cout << Stu2->Name << endl;
    cout << Stu2->Address << endl;
    cout << Stu2->Age << endl;
    return 0;
}