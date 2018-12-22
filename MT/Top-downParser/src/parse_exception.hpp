#pragma once

#include <string>
#include <stdexcept>

class parse_exception : public std::runtime_error
{
public:
    explicit parse_exception (const std::string& what_arg);
    explicit parse_exception (const char* what_arg);
};
