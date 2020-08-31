#include "ex01.h"
#include <iostream>
using namespace std;

void f1(char b){
    cout << "function f1(char b): " << endl;
    cout << "input(char): " << b << endl;
}

char f2(int c){
    cout << "function f2(int c): " << endl;
    cout << "input(int): " << c << endl;
    return 'f2';
}

int f3(float d){
    cout << "function f3(float d): " << endl;
    cout << "input(float): " << d << endl;
    return (int)d;
}

float f4(void){
    cout << "function f4(void): " << endl;
    cout << "input(void): " << "No parameters!!!" << endl;
    return 9.9;
}