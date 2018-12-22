#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include "expr.hpp"
#include "sttm.hpp"

class if_sttm : public sttm
{
public:
    if_sttm(std::shared_ptr<expr> &&, std::shared_ptr<sttm> &&, std::shared_ptr<sttm> &&);
    std::string str(unsigned int nest, 
        std::unordered_set<std::string> & declared_vars) const;
    
private:
    const std::shared_ptr<expr> _cond;
    const std::shared_ptr<sttm> _then;
    const std::shared_ptr<sttm> _else;
};
