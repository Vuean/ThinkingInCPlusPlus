#include <iostream>
using namespace std;

struct Link{
    int LinkID;
    Link* next_link;
};

void build_link(Link* link, int count)
{
    Link* new_link;
    for (int i = 0; i < count; i++)
    {
        new_link = new Link;
        new_link->next_link = 0;
        new_link->LinkID = link->LinkID + 1;
        link->next_link = new_link;
        link = new_link;
    }
}

void print(Link* link)
{
    while(link->next_link)
    {
        cout << link->LinkID << endl;
        link = link->next_link;
    }
}

int main()
{
    Link l;
    l.LinkID = 0;
    build_link(&l, 10);

    print(&l);
}