#include <iostream>

int main()
{
    double array1[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6};
    double* const const_pd = array1;

    for(int i = 0; i < sizeof(array1)/sizeof(*array1); i++)
    {
        std::cout << *(const_pd + i) << std::endl;
        *const_pd += i;
        std::cout << "The value of const_pd: " << *(const_pd) << std::endl;
        std::cout << "array1[0] = " << array1[0] << std::endl;
        // const_pd++;
    }
}