#include <ctime>
#include <iostream>

int main()
{
    const time_t current_time = time(NULL);
    struct tm* timeinfo = localtime(&current_time);
    std::cout << "Current time: " << asctime(timeinfo) << std::endl;
}