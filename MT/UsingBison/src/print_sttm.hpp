#pragma once

#include <list>
#include <memory>
#include <string>
#include <unordered_set>
#include "expr.hpp"
#include "sttm.hpp"

class print_sttm : public sttm
{
public:
    print_sttm(std::list<std::shared_ptr<expr>> &&);
    std::string str(unsigned int nest, 
        std::unordered_set<std::string> & declared_vars) const;
    
private:
    const std::list<std::shared_ptr<expr>> _exps;
};
