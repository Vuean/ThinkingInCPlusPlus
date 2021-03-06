// C14_14_Instrument.cpp
// Inheritance & upcasting
enum note {middleC, Csharp, Cflat};

class Instrument
{
public:
    void play(note) const {}
};

// Wind objects are Instruments
// because they have the same interface:
class Wind : public Instrument {};

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