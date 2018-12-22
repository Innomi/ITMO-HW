#include "str_utility.hpp"

void add_tabs(unsigned int n, std::string & s)
{
    for (size_t i = 0; i < n; ++i)
    {
        s += "    ";
    }
};
