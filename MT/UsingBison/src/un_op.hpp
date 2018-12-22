#pragma once

#include <list>
#include <memory>
#include <string>
#include "expr.hpp"

class un_op : public expr
{
public:
    un_op(std::string &&, std::shared_ptr<expr> &&);
    std::list<std::string> get_vars() const;
    std::string str() const;
    
private:
    const std::string _op;
    const std::shared_ptr<expr> _exp;
};
