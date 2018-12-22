#pragma once

#include <list>
#include <memory>
#include <string>
#include <unordered_set>
#include "sttm.hpp"

class scope_sttm : public sttm
{
public:
    scope_sttm(std::list<std::shared_ptr<sttm>> &&);
    std::string str(unsigned int nest, 
        std::unordered_set<std::string> & declared_vars) const;
    
private:
    const std::list<std::shared_ptr<sttm>> _sttmseq;
};
