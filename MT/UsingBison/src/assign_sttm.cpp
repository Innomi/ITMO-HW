#include <list>
#include <utility>
#include "assign_sttm.hpp"
#include "str_utility.hpp"

assign_sttm::assign_sttm(var && v, std::shared_ptr<expr> && e) : 
    _var(std::forward<var>(v)),
    _exp(std::forward<std::shared_ptr<expr>>(e))
{};

std::string assign_sttm::str(unsigned int nest, 
    std::unordered_set<std::string> & declared_vars) const
{
    std::string vars_to_decl = "";
    if (!declared_vars.count(_var.str()))
    {
        vars_to_decl += _var.str() + ", ";
        declared_vars.emplace(_var.str());
    }
    std::list<std::string> vars = _exp->get_vars();
    for (std::string & s : vars)
    {
        if (!declared_vars.count(s))
        {
            vars_to_decl += s + ", ";
            declared_vars.emplace(s);
        }
    }
    std::string res = "";
    if (!vars_to_decl.empty())
    {
        vars_to_decl.replace(vars_to_decl.size() - 2, 2, ";\n");
        add_tabs(nest, res);
        res += "int " + vars_to_decl;
    }
    add_tabs(nest, res);
    res += _var.str() + " = " + _exp->str() + ";\n";
    return res;
};
