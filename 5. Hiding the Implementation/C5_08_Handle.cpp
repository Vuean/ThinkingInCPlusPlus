// C5: C5_08_Handle.cpp
// Handle implementation
#include "C5_08_Handle.h"

// Define Handle's implementation:
struct Handle::Cheshire
{
    int i;
};

void Handle::initialize()
{
    smile = new Cheshire;
    smile->i = 0;
}

void Handle::cleanup()
{
    delete smile;
}

int Handle::read()
{
    return smile->i;
}

void Handle::change(int x)
{
    smile->i = x;
}