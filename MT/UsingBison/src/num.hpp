#pragma once

#include <list>
#include <string>
#include "expr.hpp"

class num : public expr
{
public:
    num(std::string &&);
    std::list<std::string> get_vars() const;
    std::string str() const;
    
private:
    const std::string _num;
};
