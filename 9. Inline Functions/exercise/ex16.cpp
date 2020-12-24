#include <iostream>
#include <string>
#include "../../require.h"
using namespace std;

#define DEBUG(x) cout << #x "=" << x << endl;

int main(int argc, char* argv[])
{
    requireArgs(argc, 1);
    string entered_string = argv[1];
    cout << "Now we will clean entered string. Please, press Enter to stop." << endl;
    
    while (std::cin.get() != '\n') 
    {
		entered_string.erase(entered_string.length() - 1, 1);
		DEBUG(entered_string);
	}
}