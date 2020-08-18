// C03:10_CatsInHats.cpp
// Simple demonstration of recursion

#include <iostream>
using namespace std;

void removeHat(char cat)
{
    for(char c = 'A'; c < cat; c++)
        cout << " ";
    if(cat <= 'Z'){
        cout << "cat " << cat << endl;
        removeHat(cat+1);
    }
    else
        cout << "VOOM!!!" << endl;
}

int main()
{
    removeHat ('A');
}