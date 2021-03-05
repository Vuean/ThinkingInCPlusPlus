// C14_07_Order.cpp
// Constructor/destructor order
#include <fstream>
using namespace std;
ofstream out("order.out");

#define CLASS(ID) class ID {\
public:\
    ID(int) { out << #ID " constructor\n"; } \
    ~ID() { out << #ID " destructor\n"; } \
};

CLASS (Base1);
CLASS (Member1);
CLASS (Member2);
CLASS (Member3);
CLASS (Member4);
