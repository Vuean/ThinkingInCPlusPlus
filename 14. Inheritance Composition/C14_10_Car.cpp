// C14_10_Car.cpp
// Public composition

class Engine
{
public:
    void start() const {}
    void rev() const {}
    void sttop() const {}
};

class Wheel
{
public:
    void inflate(int psi) const {}
};

class Window
{
public:
    void rollup() const {}
    void rolldown() const {}
};

class Door
{
public:
    Window window;
    void open() const {}
    void close() const {}
};

class Car
{
public:
    Engine engine;
    Wheel wheel[4];
    Door left, right;
};

int main()
{
    Car car;
    car.left.window.rollup();
    car.wheel[0].inflate(72);
}