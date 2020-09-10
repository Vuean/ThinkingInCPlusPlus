#include <iostream>
using namespace std;

struct Link{
    int LinkID;
    Link* next_link;
    void build_link(int count);
    void print();
};

void Link::build_link(int count)
{
    Link* new_link = new Link;
    new_link->next_link = 0;
    new_link->LinkID = LinkID + 1;
    next_link = new_link;

    if(count != 0)
        new_link->build_link(count - 1);
}

void Link::print()
{
    cout << LinkID << endl;
    if(this->next_link != 0)
    {
        this->next_link->print();
    }
}

int main()
{
    Link l;
    l.LinkID = 0;
    l.build_link(10);

    l.print();
}