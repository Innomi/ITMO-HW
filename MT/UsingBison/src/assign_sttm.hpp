#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include "expr.hpp"
#include "sttm.hpp"
#include "var.hpp"

class assign_sttm : public sttm
{
public:
    assign_sttm(var &&, std::shared_ptr<expr> &&);
    std::string str(unsigned int nest, 
        std::unordered_set<std::string> & declared_vars) const;
    
private:
    const var _var;
    const std::shared_ptr<expr> _exp;
};
