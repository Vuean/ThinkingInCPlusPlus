#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class CharClass
{
    char c;
    friend ostream& operator<<(ostream& out, const CharClass& obj);
    friend istream& operator>>(istream& is, CharClass& inputobj);
public:
    CharClass(): c(' '){}
    CharClass(char cc) : c(cc) {}
};

ostream& operator<<(ostream& out, const CharClass& obj)
{
    out << obj.c;
    return out;
}

istream& operator>>(istream& is, CharClass& inputobj)
{
    is >> inputobj.c;
    return is;
}

int main()
{
    CharClass a('A');
    CharClass b;

    cout << "Please type a single character: ";
    cin >> b;

    cout << "a = " << a << ", b = " << b << endl;

    stringstream ss;
    ss << a << b;
    cout << "stringstream ss: " << ss.str() << endl;

    stringstream ss2("D");
    CharClass d;
    ss2 >> d;
    cout << "d = " << d << endl;

    ofstream file1;
    file1.open("ex09.txt");
    CharClass e('E');
    file1 << e;
    file1.close();

    CharClass e2;
    ifstream file2;
    file2.open("ex09.txt");
    file2 >> e2;
    cout << "e2 = " << e2 << endl;

}