#include "Text.h"
#include <fstream>
using namespace std;

Text::Text()
{
    lines_count = 0;
}

Text::Text(char* fileName)
{
    ifstream in(fileName);
    string line;
    while(getline(in, line))
    {
        text.append(line);
        text.append("\n");
        lines_count++;
    }
}

Text::~Text()
{
}

string Text::contents()
{
    return text;
}