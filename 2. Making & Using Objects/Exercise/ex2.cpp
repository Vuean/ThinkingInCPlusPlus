#include <iostream>
using namespace std;

int main()
{
    int radius;
    cout << "Enter the circle radius: ";
    cin >> radius;

    if(radius < 0)
    {
        cout << "Radius must be greater than zero." << endl;
        cout << "Please try again!" << endl;
    }

    float area = 3.14 * radius * radius;

    cout << "Area of the circle with radius equal to " << radius << " is "
         << area << "." << endl;
    return 0;
}