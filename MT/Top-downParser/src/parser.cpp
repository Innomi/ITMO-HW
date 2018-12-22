#include <iostream>
#include "parser.hpp"

parser::parser() : _lex() {};

tree parser::parse(std::istream & is) throw (parse_exception)
{
    _lex = lexical_analyzer(is);
    _lex.next_token();
    return e();
};

tree parser::e() throw (parse_exception)
{
    switch (_lex.cur_token())
    {
        case (NOT) :
        case (OB) :
        case (VAR) :
        {
            tree sub = ox();
            tree cont = e_prime();
            return tree("E", std::move(sub), std::move(cont));
        }
        default :
        {
            unexp_token();
        }
    }
};

tree parser::e_prime() throw (parse_exception)
{
    switch (_lex.cur_token())
    {
        case (OR) :
        {
            _lex.next_token();
            tree sub = ox();
            tree cont = e_prime();
            return tree("E'", tree("|"), std::move(sub), std::move(cont));
        }
        case (XOR) :
        {
            _lex.next_token();
            tree sub = ox();
            tree cont = e_prime();
            return tree("E'", tree("^"), std::move(sub), std::move(cont));
        }
        case (END) :
        case (CB) :
        {
            return tree("E'", tree("eps"));
        }
        default :
        {
            unexp_token();
        }
    }
};

/*tree parser::o() throw (parse_exception)
{
    switch (_lex.cur_token())
    {
        case (NOT) :
        case (OB) :
        case (VAR) :
        {
            tree sub = x();
            tree cont = o_prime();
            return tree("O", std::move(sub), std::move(cont));
        }
        default :
        {
            unexp_token();
        }
    }
};

tree parser::o_prime() throw (parse_exception)
{
    switch (_lex.cur_token())
    {
        case (XOR) :
        {
            _lex.next_token();
            tree sub = x();
            tree cont = o_prime();
            return tree("O'", tree("^"), std::move(sub), std::move(cont));
        }
        case (OR) :
        case (END) :
        case (CB) :
        {
            return tree("O'", tree("eps"));
        }
        default :
        {
            unexp_token();
        }
    }
};*/

tree parser::ox() throw (parse_exception)
{
    switch (_lex.cur_token())
    {
        case (NOT) :
        case (OB) :
        case (VAR) :
        {
            tree sub = a();
            tree cont = ox_prime();
            return tree("OX", std::move(sub), std::move(cont));
        }
        default :
        {
            unexp_token();
        }
    }
};

tree parser::ox_prime() throw (parse_exception)
{
    switch (_lex.cur_token())
    {
        case (AND) :
        {
            _lex.next_token();
            tree sub = a();
            tree cont = ox_prime();
            return tree("OX'", tree("&"), std::move(sub), std::move(cont));
        }
        case (XOR) :
        case (OR) :
        case (END) :
        case (CB) :
        {
            return tree("OX'", tree("eps"));
        }
        default :
        {
            unexp_token();
        }
    }
};

tree parser::a() throw (parse_exception)
{
    switch (_lex.cur_token())
    {
        case (NOT) :
        {
            _lex.next_token();
            tree sub = a();
            return tree("A", tree("!"), std::move(sub));
        }
        case (OB) :
        {
            _lex.next_token();
            tree sub = e();
            if (_lex.cur_token() != CB)
            {
                std::cerr << ") expected on position " 
                << _lex.cur_pos() << "." << std::endl;
                throw parse_exception(") expected.");
            }
            _lex.next_token();
            return tree("A", tree("("), std::move(sub), tree(")"));
        }
        case (VAR) :
        {
            _lex.next_token();
            return tree("A", tree("[a..zA..Z]"));
        }
        default :
        {
            unexp_token();
        }
    }
};

void parser::unexp_token() throw (parse_exception)
{
    std::cerr << "Unexpected token on position " 
    << _lex.cur_pos() - 1 << "." << std::endl;
    throw parse_exception("Unexpected token.");
};
