#pragma once

#include <fstream>
#include "lexical_analyzer.hpp"
#include "parse_exception.hpp"
#include "tree.hpp"

class parser
{
public:
    parser();
    tree parse(std::istream & is) throw (parse_exception);

private:
    tree e() throw (parse_exception);
    tree e_prime() throw (parse_exception);
    //tree o() throw (parse_exception);
    //tree o_prime() throw (parse_exception);
    tree ox() throw (parse_exception);
    tree ox_prime() throw (parse_exception);
    tree a() throw (parse_exception);
    void unexp_token() throw (parse_exception);
    
    lexical_analyzer _lex;
};
