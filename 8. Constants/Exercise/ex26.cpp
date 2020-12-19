#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Quoter 
{
	mutable int lastquote;
public:
	Quoter();
	int lastQuote() const;
	const char* quote() const;
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

const char* Quoter::quote() const 
{
	static const char* quotes[] = 
    {
		"Are we ahving fun yet?",
		"Doctor always know best",
		"Is it ... Atomic?",
		"Fear is obscene",
		"There is no scientific evidence",
		"to support the idea",
		"that life is serious",
		"Things that make us happy, make us wise",
	};
	const int qsize = sizeof(quotes) / sizeof(*quotes);
	int qnum = rand() % qsize;
	
	while (lastquote >= 0 && qnum == lastquote)
		qnum = rand() % qsize;
	return quotes[lastquote = qnum];
}

int main() 
{
	Quoter q;
	const Quoter cq;
	cq.lastQuote();	
    //	cq.quote();	
	for (int i = 0; i < 20; i++)
		cout << q.quote() << endl;
} 