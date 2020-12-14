#ifndef TEXT_H
#define TEXT_H
#include <string>
using namespace std;

class Text
{
    int lines_count;
    std::string text;
public:
    Text();
    Text(char* fileName);
    std::string contents();
};
#endif // TEXT_H