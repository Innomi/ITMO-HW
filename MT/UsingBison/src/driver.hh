#pragma once

#include <string>
#include "main_class.hpp"
#include "prefcalc.hh"

// Give Flex the prototype of yylex we want ...
# define YY_DECL \
  yy::parser::symbol_type yylex (driver & drv)
// ... and declare it for the parser's sake.
YY_DECL;

class driver
{
public:
    driver();
    int parse(const std::string & in);
    
    bool trace_parsing;
    bool trace_scanning;
    yy::location location;
    main_class result;
    
private:
    void scan_begin();
    void scan_end();

    std::string in_file;
};
