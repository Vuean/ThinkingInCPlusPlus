// C13_08_ArrayOperatorNew.cpp
// operator new for arrays

#include <new>
#include <fstream>
using namespace std;
ofstream trace("ArrayOperatorNew.out");

class Widget
{
    enum {sz = 10};
    int i[sz];
public:
    Widget() {trace << "*"; }
    ~Widget(){trace << "~"; }
    void* operator new(size_t sz)
    {
        trace << "Widget::new: " << sz << " bytes" << endl;
        return ::new char[sz];
    }
    void operator delete(void* p)
    {
        trace << "Widget::delete: " << endl;
        return ::delete []p;
    }
    void* operator new(size_t sz)
    {
        trace << "Widget::new[]: " << sz << " bytes" << endl;
        return ::new char[sz];
    }
    void operator delete[](void* p)
    {
        trace << "Widget::delete[]: " << endl;
        return ::delete []p;
    }
};

int main()
{
    trace << "new widget" << endl;
    Widget* w = new Widget;
    trace << "\ndelete Widget" << endl;
    delete w;
    trace << "\nnew widget[25]" << endl;
    Widget* wa = new Widget[25];
    trace << "\ndelete []Widget" << endl;
    delete []wa;
}