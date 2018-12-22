#include <utility>
#include "scope_sttm.hpp"
#include "str_utility.hpp"

scope_sttm::scope_sttm(std::list<std::shared_ptr<sttm>> && sttmseq) : 
    _sttmseq(std::forward<std::list<std::shared_ptr<sttm>>>(sttmseq))
{};

std::string scope_sttm::str(unsigned int nest, 
    std::unordered_set<std::string> & declared_vars) const
{
    std::unordered_set<std::string> local_decl_vars(declared_vars);
    std::string res = "";
    add_tabs(nest, res);
    res += "{\n";
    for (std::shared_ptr<sttm> s : _sttmseq)
    {
        res += s->str(nest + 1, local_decl_vars);
    }
    add_tabs(nest, res);
    res += "}\n";
    return res;
};
