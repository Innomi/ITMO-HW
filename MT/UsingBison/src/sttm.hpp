#pragma once

#include <string>
#include <unordered_set>

class sttm
{
public:
    virtual ~sttm();
    virtual std::string str(unsigned int nest, 
        std::unordered_set<std::string> & declared_vars) const = 0;
};
