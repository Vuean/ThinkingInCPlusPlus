// C8_14_Quoter.cpp
// Random quote selection
#include <iostream>
#include <cstdlib>  // Random number generator
#include <ctime>    // To seed random generator
using namespace std;

class Quoter
{
    int lastquote;
public:
    Quoter();
    int lastQuote() const;
    const char* quote();
};

Quoter::Quoter()
{
    lastquote = -1;
    srand(time(0));
}

int Quoter::lastQuote() const
{
    return lastquote;
}

const char* Quoter::quote()
{
    static const char* quotes[] = 
    {
        "Are we having fun yet?",
        "Doctors al ways know best" ,
        "Is it ... Atomic?",
        "Fear is obscene",
        "There is no scientific evidence "
        "to support the idea "
        "that life is seriou s",
        "Things that fDake us happy, make us wise"
    };
    const int qsize = sizeof(quotes) / sizeof(*quotes);
    int qnum = rand() % qsize;
    while(lastquote >= 0 && qnum == lastquote)
        qnum = rand() % qsize;
    return quotes[lastquote = qnum];
}

int main()
{
    Quoter q;
    const Quoter cq;
    cq.lastQuote();
    // cq.quote();  // Illegal, non const function
    for(int i = 0; i < 20; i++)
        cout << q.quote() << endl;
}