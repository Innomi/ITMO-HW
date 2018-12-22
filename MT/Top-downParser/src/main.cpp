#include <exception>
#include <iostream>
#include <list>
#include <string>
#include "lexical_analyzer.hpp"
#include "parser.hpp"
#include "parser_tester.hpp"
#include "tree.hpp"

int main()
{
    parser_tester tester;
    tester.test({
        "a&a",                                      //Test for &
        "A|A",                                      //Test for |
        "A^a",                                      //Test for ^
        "!a",                                       //Test for !
        "!a&a^f|d",                                 //Test for operation priority
        "(a)^!(b|!t)",                              //Test with brackets
        "((a|b)&((v^v&i)|j))",                      //Test with more brackets
        "(a      ^ \t\t\t\n\n\n b)   \n \t & c",    //Test with additional space symbols for lexer
        "!!!!!!!!!!!a & a"                          //Test with multiple negation
    });
    tester.fail_test({
        "qw",       //Variable should be made from a single letter
        "1 | g",    //Numbers is forbidden
        "a + b",    //Forbidden operation
        "(((a|b)",  //Test for brackets balance check
        "a || b",   //Forbidden operation
        "()"        //Empty braces are not allowed
    });
    tester.drawing_test({   //Some drawing tests
        "a|a^a",
        "(b^a)&c", 
        "a|a|a|g|g|b", 
        "(a^c)&(f&a)"
    });
    tester.random_test(10, 6); //Some random tests
    return 0;
}
