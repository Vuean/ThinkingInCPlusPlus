#include <iostream>
using namespace std;

int main()
{
    for(int i = 1; i < 1000; ++i){
        for(int j = 2; j < i; ++j){
            if(i % j == 0 && i != j){
                break;
            }
            else if(i % j == 0 && i == j){
                cout << i << " is prime number" << endl;
            }
        }
    }
}