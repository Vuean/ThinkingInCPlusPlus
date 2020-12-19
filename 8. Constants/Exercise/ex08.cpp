#include <iostream>

int main()
{
    const long* array1; //  = {1, 2, 3, 4, 5}
    long const* array2; //  = {6, 7, 8, 9, 10}
    long array3[] = {1, 2, 3, 4, 5, 6, 7};

    array2 = array3;
    array1 = array3;

    std::cout << "Size of array1: " << sizeof(array1)/ sizeof(*array1) << std::endl;
    for(int i = 0; i < sizeof(array3) / sizeof(*array3); i++)
    {
        std::cout << *array1 << std::endl;
        *array1++;
        // *array1 = 5; // Error
    }
}