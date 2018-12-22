#include <utility>
#include "un_op.hpp"

un_op::un_op(std::string && op, std::shared_ptr<expr> && e) : 
    _op(std::forward<std::string>(op)), 
    _exp(std::forward<std::shared_ptr<expr>>(e))
{};

std::list<std::string> un_op::get_vars() const
{
    return _exp->get_vars();
};

std::string un_op::str() const
{
    return _op + _exp->str();
};
