#include <utility>
#include "bin_op.hpp"

bin_op::bin_op(std::string && op, std::shared_ptr<expr> && l, std::shared_ptr<expr> && r) : 
    _op(std::forward<std::string>(op)), 
    _l(std::forward<std::shared_ptr<expr>>(l)), 
    _r(std::forward<std::shared_ptr<expr>>(r))
{};

std::list<std::string> bin_op::get_vars() const
{
    std::list<std::string> vars = _l->get_vars();
    vars.splice(vars.end(), _r->get_vars());
    return vars;
};

std::string bin_op::str() const
{
    return "(" + _l->str() + " " + _op + " " + _r->str() + ")";
};
