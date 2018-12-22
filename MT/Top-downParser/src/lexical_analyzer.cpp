#include <iostream>
#include "lexical_analyzer.hpp"

lexical_analyzer::lexical_analyzer() {};

lexical_analyzer::lexical_analyzer(lexical_analyzer && other) : 
    _is(std::move(other._is)), _cur_char(std::move(other._cur_char)), 
    _cur_pos(std::move(other._cur_pos)), _cur_token(std::move(other._cur_token)) {};

lexical_analyzer::lexical_analyzer(std::istream & is) throw (parse_exception) : 
    _is(&is), _cur_pos(0)
{
    next_char();
};

lexical_analyzer & lexical_analyzer::operator=(lexical_analyzer && other)
{
    _is = std::move(other._is);
    _cur_char = std::move(other._cur_char);
    _cur_pos = std::move(other._cur_pos);
    _cur_token = std::move(other._cur_token);
    return *this;
};

void lexical_analyzer::next_token() throw (parse_exception)
{
    while (is_blank(_cur_char))
    {
        next_char();
    }
    switch (_cur_char)
    {
        case ('(') :
        {
            _cur_token = OB;
            break;
        }
        case (')') :
        {
            _cur_token = CB;
            break;
        }
        case ('&') :
        {
            _cur_token = AND;
            break;
        }
        case ('|') :
        {
            _cur_token = OR;
            break;
        }
        case ('^') :
        {
            _cur_token = XOR;
            break;
        }
        case ('!') :
        {
            _cur_token = NOT;
            break;
        }
        case (EOF) :
        {
            _cur_token = END;
            break;
        }
        default :
        {
            if ((_cur_char >= 'a' && _cur_char <= 'z') 
             || (_cur_char >= 'A' && _cur_char <= 'Z'))
            {
                _cur_token = VAR;
            }
            else
            {
                std::cerr << "Illegal character " << _cur_char 
                << " on position " << _cur_pos << std::endl;
                throw parse_exception("Illegal character.");
            }
        }
    }
    if (_cur_token != END)
    {
        next_char();
    }
};

token lexical_analyzer::cur_token()
{
    return _cur_token;
};

int lexical_analyzer::cur_pos()
{
    return _cur_pos;
};

void lexical_analyzer::next_char() throw (parse_exception)
{
    ++_cur_pos;
    try
    {
        _cur_char = _is->get();
    }
    catch (std::exception & e)
    {
        std::cerr << e.what() << "(pos: " << _cur_pos << ")" << std::endl;
        throw parse_exception(e.what());
    }
};

bool lexical_analyzer::is_blank(char c)
{
    return c == ' ' || c == '\r' || c == '\n' || c == '\t';
};
