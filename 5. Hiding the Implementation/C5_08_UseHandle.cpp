// C05: C5_08_UseHandle.cpp
// USe the Handle class
#include "C5_08_Handle.h"

int main()
{
    Handle h;
    h.initialize();
    h.read();
    h.change(1);
    h.cleanup();
}