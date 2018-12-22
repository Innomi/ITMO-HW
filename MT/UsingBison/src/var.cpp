#include <utility>
#include "var.hpp"

var::var(std::string && name) : _name(std::forward<std::string>(name))
{};

std::list<std::string> var::get_vars() const
{
    return std::list<std::string>({ _name });
};

std::string var::str() const
{
    return _name;
};
