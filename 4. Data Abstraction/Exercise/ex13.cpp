#include "ex13.h"
#include <iostream>
using namespace std;

void Vedio::print()
{
    cout << "Film name: " << name << endl;
    cout << "Film duration: " << duration << endl;
    cout << "Film cost: " << cost << endl;
    cout << "Film actors: ";
    for(int i = 0; i < actors.size(); i++)
        cout << actors[i] << "; ";
    cout << endl;
}

void Vedio::release()
{
    isReleased = true;
}

void Vedio::initialize()
{
    name = "";
    duration = 0.00;
    cost = 0.00;
    isReleased = false;
}

int main()
{
    Vedio v;
}