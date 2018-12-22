#include <utility>
#include "print_sttm.hpp"
#include "str_utility.hpp"

print_sttm::print_sttm(std::list<std::shared_ptr<expr>> && exps) : 
    _exps(std::forward<std::list<std::shared_ptr<expr>>>(exps))
{};

std::string print_sttm::str(unsigned int nest, 
    std::unordered_set<std::string> & declared_vars) const
{
    std::string vars_to_decl = "";
    for (std::shared_ptr<expr> e : _exps)
    {
        std::list<std::string> vars = e->get_vars();
        for (std::string s : vars)
        {
            if (!declared_vars.count(s))
            {
                vars_to_decl += s + ", ";
                declared_vars.emplace(s);
            }
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
    res += "printf(\"";
    for (size_t i = 0; i < _exps.size(); ++i)
    {
        res += "%d ";
    }
    res += "\\n\"";
    for (std::shared_ptr<expr> e : _exps)
    {
        res += ", " + e->str();
    }
    res += ");\n";
    return res;
};
