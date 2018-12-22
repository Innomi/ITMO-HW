#include "parse_exception.hpp"

parse_exception::parse_exception (const std::string& what_arg) : 
    std::runtime_error(what_arg) {};

parse_exception::parse_exception (const char* what_arg) :
    std::runtime_error(what_arg) {};
