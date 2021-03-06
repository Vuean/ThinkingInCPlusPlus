// C15_03_Instrument4.cpp
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
    virtual char* what() const
    {
        return "Instrument";
    }
    virtual void adjust(int){}
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
    char* what() const { return "Wind"; }
    void adjust(int) {}
};

class Percussion : public Instrument
{
public:
    void play(note) const
    {
        cout << "Percussion::play" << endl;
    }
    char* what() const { return "Percussion"; }
    void adjust(int) {}
};

class Stringed : public Instrument
{
public:
    void play(note) const
    {
        cout << "Stringed::play" << endl;
    }
    char* what() const { return "Stringed"; }
    void adjust(int) {}
};

class Brass : public Wind
{
public:
    void play(note) const
    {
        cout << "Brass::play" << endl;
    }
    char* what() const { return "Brass"; }
};

class Woodwind : public Wind
{
public:
    void play(note) const
    {
        cout << "Woodwind::play" << endl;
    }
    char* what() const { return "Woodwind"; }
};

void tune(Instrument& i)
{
    // ....
    i.play(middleC);
}

void f(Instrument& i)
{
    i.adjust(1);
}

Instrument* A[] = {
    new Wind,
    new Percussion,
    new Stringed,
    new Brass,
};

int main()
{
    Wind flute;
    Percussion drum;
    Stringed violin;
    Brass flugelhorn;
    Woodwind recorder;
    tune(flute);
    tune(drum);
    tune(violin);
    tune(flugelhorn);
    tune(recorder);
    f(flugelhorn);
}