// C10_23_Initializer.h
// Static initialization technique
#ifndef INITIALIZER_H
#define INITIALIZER_H
#include <iostream>
extern int x; // Declarations, not definitions
extern int y;

class Initializer 
{
    static int initCount;
public:
    Initializer()
    {
        std::cout << "Initializer() " << std::endl;
        // Initialize first time only
        if (initCount++ == 0)
        {
            std::cout << "performing initialization" << std::endl;
        }
        x = 100;
        y = 200;
    }
    ~Initializer() 
    {
        std::cout << "~Initializer()" << std::endl;
        // Clean up last time only
        if(--initCount == 0)
            std::cout << "performing cleanup" << std::endl;
        // Any necessary cleanup heer
    }
};
// The following creates one object in each
// file where I nitializer.h is included, but that
// object is only visible within that file:
static Initializer init;
#endif // INITIALIZER_H