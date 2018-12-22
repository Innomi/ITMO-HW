#include <list>
#include <utility>
#include "while_sttm.hpp"
#include "str_utility.hpp"

while_sttm::while_sttm(std::shared_ptr<expr> && cond, std::shared_ptr<sttm> && st) : 
    _cond(std::forward<std::shared_ptr<expr>>(cond)),
    _sttm(std::forward<std::shared_ptr<sttm>>(st))
{};

std::string while_sttm::str(unsigned int nest, 
    std::unordered_set<std::string> & declared_vars) const
{
    std::string vars_to_decl = "";
    std::list<std::string> vars = _cond->get_vars();
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
    std::unordered_set<std::string> local_decl_vars(declared_vars);
    add_tabs(nest, res);
    res += "while (" + _cond->str() + ")\n";
    add_tabs(nest, res);
    res += "{\n" + _sttm->str(nest + 1, local_decl_vars);
    add_tabs(nest, res);
    res += "}\n";
    return res;
};
