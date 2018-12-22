#pragma once

#include <list>
#include <string>

class expr
{
public:
    virtual ~expr();
    virtual std::list<std::string> get_vars() const = 0;
    virtual std::string str() const = 0;
};
