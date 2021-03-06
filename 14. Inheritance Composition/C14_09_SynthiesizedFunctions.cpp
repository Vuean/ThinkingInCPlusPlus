// C14_09_SynthiesizedFunctions.cpp
// Functions that are synthiesized by the complier

#include <iostream>
using namespace std;

class GameBoard
{
public:
    GameBoard()
    {
        cout << "GameBoard() \n";
    }
    GameBoard(const GameBoard&)
    {
        cout << "GameBoard(const GameBoard&) \n";
    }
    GameBoard& operator=(const GameBoard&)
    {
        cout << "GameBoard& operator=(const GameBoard&) \n";
        return *this;
    }
    ~GameBoard()
    {
        cout << "~GameBoard() \n";
    }
};

class Game
{
    GameBoard gb;   // Compisition
public:
    // Default GameBoard constructor called:
    Game()
    {
        cout << "Game() \n";
    }
    // You must explicitly call the GameBoard
    // copy-constructor or the default constructor
    // is automatically called instead:
    Game(const Game& g) : gb(g.gb)
    {
        cout << "Game(const Game&) \n";
    }
    Game(int)
    {
        cout << "Game(int) \n";
    }
    Game& operator=(const Game& g)
    {
        // You must explicitly call the GameBoard
        // assignment operator or no assignment at
        // all happens for gb:
        gb = g.gb;
        cout << "Game::operator=()\n";
        return *this;
    }
    class Other {};  // Nested class
    // Automatic type conversion:
    operator Other() const
    {
        cout << "Game::operator Other() \n";
        return Other();
    }
    ~Game()
    {
        cout << "~Game() \n";
    }
};

class Chess : public Game
{

};

void f(Game::Other) {}

class Checkers : public Game
{
public:
    // Default base-class constructor called:
    Checkers()
    {
        cout << "Checkers() \n";
    }
    // You must explicitly call the base class
    // copy constructor or the default constructor
    // will be automatically called instead:
    Checkers(const Checkers& c) : Game(c)
    {
        cout << "Checkers(const Checkers&) \n";
    }
    Checkers& operator=(const Checkers& c)
    {
        // You must explicitly call the base-class
        // version of opertor=() or no base-class
        // assigment will happen:
        Game::operator=(c);
        cout << "Checkers& operator=() \n";
        return *this;
    }
};

int main()
{
    Chess d1;   // default constructor
    Chess d2(d1);   // copy constructor
    // Chess d3(1);    // Error no int constructor
    d1 = d2;    // operator=() synthiesized
    f(d1);      // Type-conversion is inherited
    Game::Other go;
    // d1 = go;     // Operator= not synthiesized for differing types
    Checkers c1, c2(c1);
    c1 = c2;
}