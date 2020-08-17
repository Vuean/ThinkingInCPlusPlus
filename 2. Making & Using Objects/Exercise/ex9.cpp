#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

int main()
{
    vector<float> FloatVec1;
    vector<float> FloatVec2;
    vector<float> FloatVec3;

    for (int i = 0; i < 25; i++)
    {
        float randnum1 = (float) std::rand() / ((float)RAND_MAX/20);
        float randnum2 = (float) std::rand() / ((float)RAND_MAX/20);
        FloatVec1.push_back(randnum1);
        FloatVec2.push_back(randnum2);
    }
    
    for(int i = 0; i < FloatVec1.size(); i++)
    {
        FloatVec3.push_back(FloatVec1[i] + FloatVec2[i]);
    }

    cout << "FloatVec1: " << endl;
    for(int i = 0; i < FloatVec1.size(); i++)
        cout << FloatVec1[i] << ", ";
    
    cout << "FloatVec2: " << endl;
    for(int i = 0; i < FloatVec2.size(); i++)
        cout << FloatVec2[i] << ", ";
    
    cout << "FloatVec3: " << endl;
    for(int i = 0; i < FloatVec3.size(); i++)
        cout << FloatVec3[i] << ", ";
    
    cout << endl;
    return 0;
}