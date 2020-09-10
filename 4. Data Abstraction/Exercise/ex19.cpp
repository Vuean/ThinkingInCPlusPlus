#include <iostream>
#include <string>
using namespace std;

struct Person
{
    struct PersonName{
        string name;
        string surname;
        string middlename;
        void print();
    };
    PersonName name;
    int age;
    char sex;
    void print();
};

void Person::PersonName::print()
{
    cout << surname << " " << name << " " << middlename << endl;
}

void Person::print()
{
    cout << "Age: " << age << endl;
    cout << "Sex: " << sex << endl;
}

int main()
{
    Person p;
    p.name.name = "Jane";
    p.name.surname = "Smith";
    p.name.middlename = "John";
    p.age = 30;
    p.sex = 'M';

    p.name.print();
    p.print();
}