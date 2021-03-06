// C14_12_PrivateInheritance.cpp
class Pet
{
public:
    char eat() const { return 'a'; }
    int speak() const { return 2; }
    float sleep() const { return 3.0; }
    float sleep(int) const { return 4.0; }
};

class Goldfish : Pet    // Private inheritance
{
public:
    using Pet::eat; // Name publicizes member
    using Pet::sleep; // Both members exposed
};

int main()
{
    Goldfish gf;
    gf.eat();
    gf.sleep();
    gf.sleep(1);
    // gf.speak();  // Error: private member function
}