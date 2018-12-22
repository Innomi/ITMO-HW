#include <fstream>
#include <unordered_set>
#include <utility>
#include "main_class.hpp"

main_class::main_class()
{};

main_class::main_class(std::list<std::shared_ptr<sttm>> && sttmseq) :
    _sttmseq(std::forward<std::list<std::shared_ptr<sttm>>>(sttmseq))
{};

main_class& main_class::operator =(main_class && other)
{
    this->_sttmseq = std::move(other._sttmseq);
    return *this;
};

void main_class::print(std::string && filename) const
{
    std::ofstream out(filename);
    out << "#include <stdio.h>\n\n";
    out << "int main()\n{\n";
    std::unordered_set<std::string> declared_vars;
    for (std::shared_ptr<sttm> s : _sttmseq)
    {
        out << s->str(1, declared_vars);
    }
    out << "    return 0;\n";
    out << "}" << std::endl;
};
