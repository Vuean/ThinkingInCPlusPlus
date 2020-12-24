#include <iostream>
#include "../../require.h"
using namespace std;

int main(int argc, char* argv[])
{
    requireArgs(argc, 2);
    require(atoi(argv[1]) >= 5);
    require(atoi(argv[1]) <= 10);

    char* file_name = argv[2];
    ifstream in(file_name);

    assure(in, file_name);
}