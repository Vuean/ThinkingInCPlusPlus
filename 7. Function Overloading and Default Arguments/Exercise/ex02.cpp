#include <string>
#include <iostream>
using namespace std;

class Message
{
    string message;
public:
    Message(string = "dumb message");
    ~Message();
    void print();
    void print(string another_message);
};

Message::Message(string incoming_message)
{
    message = incoming_message;
}

Message::~Message()
{}

void Message::print()
{
    cout << message << endl;
}

void Message::print(string another_message)
{
    cout << message << " " << another_message << endl;
}

int main()
{
    Message m1;
    Message m2("Ex02_Message");
    m1.print();
    m1.print("With another message");
    m2.print();
    m2.print("With another message");
}