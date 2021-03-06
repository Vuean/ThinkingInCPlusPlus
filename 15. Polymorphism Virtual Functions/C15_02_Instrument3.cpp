// C15_02_Instrument3.cpp
// Late bidding with the virtual keyword
#include <iostream>
using namespace std;
enum note {middleC, Csharp, Cflat};

class Instrument
{
public:
    virtual void play(note) const 
    {
        cout << "Instrument::play" << endl;
    }
};

// Wind objects are Instruments
// because they have the same interface:
class Wind : public Instrument 
{
public:
    // Redefine interface function:
    void play(note) const
    {
        cout << "Wind::play" << endl;
    }
};

void tune(Instrument& i)
{
    // ....
    i.play(middleC);
}

int main()
{
    Wind flute;
    tune(flute);
}