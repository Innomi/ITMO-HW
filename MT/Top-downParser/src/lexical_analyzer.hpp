#pragma once

#include <fstream>
#include "parse_exception.hpp"

enum token { OB, CB, AND, OR, XOR, NOT, VAR, END };

class lexical_analyzer
{
public:
    lexical_analyzer();
    lexical_analyzer(const lexical_analyzer & lex) = delete;
    lexical_analyzer(lexical_analyzer && lex);
    lexical_analyzer(std::istream & is) throw (parse_exception);
    lexical_analyzer & operator=(const lexical_analyzer & other) = delete;
    lexical_analyzer & operator=(lexical_analyzer && other);
    void next_token() throw (parse_exception);
    token cur_token();
    int cur_pos();

private:
    void next_char() throw (parse_exception);
    bool is_blank(char c);

    std::istream * _is;
    char _cur_char;
    int _cur_pos;
    token _cur_token;
};
