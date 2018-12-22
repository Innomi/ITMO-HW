#pragma once

#include <list>
#include <string>
#include "expr.hpp"

class var : public expr
{
public:
    var(std::string &&);
    std::list<std::string> get_vars() const;
    std::string str() const;
    
private:
    const std::string _name;
};
