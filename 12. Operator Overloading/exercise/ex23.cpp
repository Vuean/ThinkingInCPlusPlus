#include <string>
#include <iostream>
using namespace std;
class Dog
{
    string nm;
    int refcount;
    int counter;
    static int overall;

    Dog(const string& name) : nm(name), refcount(1), counter(0)
    {
        counter = ++overall;
        cout << "Creating Dog: " << *this << "(" << counter << ")" << endl;
        cout << "Overall dogs: " << overall << endl;
    }
    // Prevent assignment
    Dog& operator=(const Dog& rv);
public:
    // Dog can only be created on the heap:
    static Dog* make(const string& name)
    {
        return new Dog(name);
    }
    Dog(const Dog& d) : nm(d.nm + " copy"), refcount(1)
    {
        cout << "Dog copy-constructor: " << *this << endl;
    }
    ~Dog()
    {
        cout << "Deleting Dog: " << *this << endl;
    }
    void attach()
    {
        ++refcount;
        cout << "Attach Dog: " << *this << endl;
    }
    void detach()
    {
        cout << "Detach Dog: " << *this << endl;
        // Destory object if no one is using it:
        if(--refcount == 0) delete this;
    }
    // Conditional copy this Dog.
    // Call before nodifying the Dog, assign resulting pointer to your Dog*.
    Dog* unalias()
    {
        cout << "Unaliasing Dog: " << *this << endl;
        // Don't duplicate if not called:
        if(refcount == 1) return this;
        --refcount;
        // Use copy-constructor to duplicate:
        return new Dog(*this);
    }
    void rename(const string& newName)
    {
        nm = newName;
        cout << "Dog renamed to: " << *this << endl;
    }
    friend ostream& operator<<(ostream& os, const Dog& d)
    {
        return os << "[" << d.nm << "], rc = " << d.refcount;
    }
};

class DogHouse
{
    Dog* p;
    string houseName;
    int counter;
    static int overall;
public:
    DogHouse(Dog* dog, const string& house)
        : p(dog), houseName(house), counter(0) 
    {
        counter = ++overall;
        cout << "Created DogHouse: " << "(" << counter << ")" << endl;
        cout << "Overall doghouses: " << overall << endl;
    }
    DogHouse(const DogHouse& dh)
        : p(dh.p), houseName("copy-constructed" + dh.houseName) 
    {
        p->attach();
        counter = dh.counter + 1;
        overall++;
        cout << "DogHouse copy-constructor: " << *this << "(" << counter << ")" << endl;
        cout << "Overall doghouses: " << overall << endl;
    }
    DogHouse& operator=(const DogHouse& dh)
    {
        // Check for self-assignment
        if(&dh != this)
        {
            houseName = dh.houseName + " assigned";
            // Clean up what you're using first:
            p->detach();
            p = dh.p;   // like copy-constructor
            p->attach();
        }
        cout << "DogHouse operator= : " << *this << endl;
        return *this;
    }
    // Decrement refcount, conditionally destory
    ~DogHouse()
    {
        cout << "DogHouse Destructors: " << *this << endl;
        p->detach();
    }
    void renameHouse(const string& newName)
    {
        houseName = newName;
    }
    void unalias() {p->unalias();}
    // Copy-on-write. Anytime you modify the contents of the pointer 
    // you must first unalias it:
    void renameDog(const string& newName)
    {
        unalias();
        p->rename(newName);
    }
    // .. or when you allow someone else access:
    Dog* getDog() 
    { 
        unalias();
        return p;
    }
    
    friend ostream& operator<<(ostream& os, const DogHouse& dh)
    {
        return os << "[" << dh.houseName << "] contains" << *dh.p;
    }
};

int Dog::overall = 0;
int DogHouse::overall = 0;

int main()
{
    DogHouse fidos(Dog::make("Fido"), "FidoHouse"),
            spots(Dog::make("Spot"), "SpotHouse");
    cout << "Entering copy-construction" << endl;
    DogHouse bobs(fidos);
    cout << "After copy-constructing bobs:" << endl;
    cout << "fidos: " << fidos << endl;
    cout << "spots: " << spots << endl;
    cout << "bobs: " << bobs << endl;
    cout << "Entering spots = fidos" << endl;
    spots = fidos;
    cout << "After spots = fidos" << endl;
    cout << "spots: " << spots << endl;
    cout << "Entering self-assignment" << endl;
    bobs = bobs;
    cout << "After self-assignment" << endl;
     cout << "bobs: " << bobs << endl;
     // Comment out the following lines:
    cout << "Entering rename(\"Bob\") " << endl;
    bobs.getDog()->rename("Bob");
    cout << "After rename(\"Bob\") " << endl;
}