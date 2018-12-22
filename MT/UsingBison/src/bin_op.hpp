#pragma once

#include <list>
#include <memory>
#include <string>
#include "expr.hpp"

class bin_op : public expr
{
public:
    bin_op(std::string &&, std::shared_ptr<expr> &&, std::shared_ptr<expr> &&);
    std::list<std::string> get_vars() const;
    std::string str() const;
    
private:
    const std::string _op;
    const std::shared_ptr<expr> _l;
    const std::shared_ptr<expr> _r;
};
