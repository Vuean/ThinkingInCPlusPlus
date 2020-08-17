#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

int main()
{
    vector<float> FloatVec;

    for (int i = 0; i < 25; i++)
    {
        float randnum = (float) std::rand() / ((float)RAND_MAX/20);
        FloatVec.push_back(randnum);
    }
    
    for(int i = 0; i < FloatVec.size(); i++)
        cout << FloatVec[i] << " ";
    
    cout << endl;
    return 0;
}