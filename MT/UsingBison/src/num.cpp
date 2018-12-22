#include <utility>
#include "num.hpp"

num::num(std::string && n) : _num(std::forward<std::string>(n))
{};

std::list<std::string> num::get_vars() const
{
    return std::list<std::string>();
};

std::string num::str() const
{
    return _num;
};
