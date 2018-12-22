%{
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <string>
#include "driver.hh"
#include "prefcalc.hh"
%}

%option noyywrap nounput noinput batch debug

%{
    yy::parser::symbol_type make_NUM(const std::string & s, 
            const yy::parser::location_type & loc);
%}

id    [a-zA-Z_][a-zA-Z_0-9]*
int   -?[0-9]+
blank [ \t\r]

%{
//Code runs each time a pattern is matched.
#define YY_USER_ACTION loc.columns(yyleng);
%}
%%
%{
    yy::location& loc = drv.location;
    loc.step();
%}

{blank}+ loc.step();
\n+      loc.lines(yyleng); loc.step();

"=="     return yy::parser::make_EQ    (loc);
"!="     return yy::parser::make_NEQ   (loc);
">="     return yy::parser::make_GEQ   (loc);
"<="     return yy::parser::make_LEQ   (loc);
"="      return yy::parser::make_ASSGN (loc);
"?"      return yy::parser::make_IF    (loc);
":"      return yy::parser::make_ELSE  (loc);
"("      return yy::parser::make_OB    (loc);
")"      return yy::parser::make_CB    (loc);
"@"      return yy::parser::make_PRNT  (loc);
";"      return yy::parser::make_END   (loc);
"+"      return yy::parser::make_ADD   (loc);
"-"      return yy::parser::make_SUB   (loc);
"*"      return yy::parser::make_MUL   (loc);
"/"      return yy::parser::make_DIV   (loc);
"%"      return yy::parser::make_MOD   (loc);
"!"      return yy::parser::make_NOT   (loc);
"&"      return yy::parser::make_AND   (loc);
"|"      return yy::parser::make_OR    (loc);
">"      return yy::parser::make_GRT   (loc);
"<"      return yy::parser::make_LSS   (loc);
"#"      return yy::parser::make_WHILE (loc);

{int}    return make_NUM(yytext, loc);
{id}     return yy::parser::make_VAR(yytext, loc);
.        {
    throw yy::parser::syntax_error
    (loc, "invalid character: " + std::string(yytext));
}

<<EOF>>  return yy::parser::make_EOF   (loc);
%%

yy::parser::symbol_type make_NUM(const std::string & s, 
        const yy::parser::location_type & loc)
{
    errno = 0;
    long long n = strtoll(s.c_str(), NULL, 10);
    if (!(INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
    {
        throw yy::parser::syntax_error(loc, "integer is out of range: " + s);
    }
    return yy::parser::make_NUM(s, loc);
}

void driver::scan_begin()
{
    yy_flex_debug = trace_scanning;
    if (in_file.empty() || in_file == "-")
    {
        yyin = stdin;
    }
    else
    {
        if (!(yyin = fopen(in_file.c_str(), "r")))
        {
            std::cerr << "cannot open " << in_file << ": " << strerror(errno) << '\n';
            exit(EXIT_FAILURE);
        }
    }
}

void driver::scan_end()
{
    fclose(yyin);
}
