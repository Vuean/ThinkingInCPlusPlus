#include "../../require.h"
#include <iostream>
using namespace std;

#define IFOPEN(VAR, NAME) \
    std::ifstream VAR(NAME); \
    assure(VAR, NAME);

int main(int argc, char* argv[])
{
    requireArgs(argc, 1);
    IFOPEN(in, argv[1]);
}