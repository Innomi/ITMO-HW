#pragma once

#include <list>
#include <sstream>
#include <string>
#include "parser.hpp"
#include "tree.hpp"

class parser_tester
{
public:
    parser_tester();
    void test(const std::list<std::string> && tests);
    void fail_test(const std::list<std::string> && tests);
    void drawing_test(const std::list<std::string> && tests);
    void random_test(unsigned int tests_count, int max_depth);
    
private:
    std::string gen_rand_expr(std::string && node, int max_depth);

    parser _prsr;
};
