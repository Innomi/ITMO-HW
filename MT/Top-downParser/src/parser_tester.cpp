#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include "parser_tester.hpp"

parser_tester::parser_tester() : _prsr() {};

void parser_tester::test(const std::list<std::string> && tests)
{
    std::cout << "Testing:" << std::endl;
    for (const std::string & str : tests)
    {
        std::istringstream is(str);
        std::cout << str << " :" << std::endl;
        try
        {
            std::cout << _prsr.parse(is).to_str() << std::endl;
        }
        catch (std::exception & e)
        {
            std::cout << "An exception is caught: " << e.what() << std::endl;
        }
        std::cout << std::endl;
    }
};


void parser_tester::fail_test(const std::list<std::string> && tests)
{
    std::cout << "Fail testing:" << std::endl;
    for (const std::string & str : tests)
    {
        std::istringstream is(str);
        std::cout << str << " :" << std::endl;
        try
        {
            std::cout << _prsr.parse(is).to_str() << std::endl;
        }
        catch (std::exception & e) 
        {
            std::cout << "An exception is caught: " << e.what() << std::endl << std::endl;
            continue;
        }
        std::cout << "An exception is not caught." << std::endl << std::endl;
    }
};

void parser_tester::drawing_test(const std::list<std::string> && tests)
{
    std::cout << "Drawing:" << std::endl;
    for (const std::string & str : tests)
    {
        std::istringstream is(str);
        std::cout << str << " :" << std::endl;
        try
        {
            _prsr.parse(is).draw(std::string(str));
            std::cout << "Drawn!" << std::endl;
        }
        catch (std::exception & e)
        {
            std::cout << "An exception is caught: " << e.what() << std::endl;
        }
        std::cout << std::endl;
    }
};

//If max_gen_depth is reached, the generator will chose rules, which lead to the end of a tree.
void parser_tester::random_test(unsigned int tests_count, int max_gen_depth)
{
    std::cout << "Random expressions testing:" << std::endl;
    std::string str;
    for (size_t i = 0; i < tests_count; ++i)
    {
        str = gen_rand_expr("E", max_gen_depth - 1);
        std::istringstream is(str);
        std::cout << str << " :" << std::endl;
        try
        {
            std::cout << _prsr.parse(is).to_str() << std::endl;
        }
        catch (std::exception & e)
        {
            std::cout << "An exception is caught: " << e.what() << std::endl;
        }
        std::cout << std::endl;
    }
};

//If max_gen_depth is reached, the generator will chose rules, which lead to the end of a tree.
std::string parser_tester::gen_rand_expr(std::string && node, int max_gen_depth)
{
    if (node == "E")
    {
        return gen_rand_expr("O", max_gen_depth - 1) 
            + gen_rand_expr("E'", max_gen_depth - 1);
    }
    if (node == "O")
    {
        return gen_rand_expr("X", max_gen_depth - 1) 
            + gen_rand_expr("O'", max_gen_depth - 1);
    }
    if (node == "X")
    {
        return gen_rand_expr("A", max_gen_depth - 1) 
            + gen_rand_expr("X'", max_gen_depth - 1);
    }
    unsigned int choice;
    if (node == "A")
    {
        choice = rand() % 3;
        if (choice == 2 || max_gen_depth < 2)
        {
            if (rand() % 2 == 1)
            {
                return std::string(1, 'a' + rand() % 26);
            }
            else
            {
                return std::string(1, 'A' + rand() % 26);
            }
        }
        if (choice == 1)
        {
            return "(" + gen_rand_expr("E", max_gen_depth - 1) + ")";
        }
        return "!" + gen_rand_expr("A", max_gen_depth - 1);
    }
    choice = rand() % 2;
    if (node == "E'")
    {
        if (choice == 1 || max_gen_depth < 2)
        {
            return "";
        }
        return "|" 
            + gen_rand_expr("O", max_gen_depth - 1) 
            + gen_rand_expr("E'", max_gen_depth - 1);
    }
    if (node == "O'")
    {
        if (choice == 1 || max_gen_depth < 2)
        {
            return "";
        }
        return "^" 
            + gen_rand_expr("X", max_gen_depth - 1) 
            + gen_rand_expr("O'", max_gen_depth - 1);
    }
    if (node == "X'")
    {
        if (choice == 1 || max_gen_depth < 2)
        {
            return "";
        }
        return "&" 
            + gen_rand_expr("A", max_gen_depth - 1) 
            + gen_rand_expr("X'", max_gen_depth - 1);
    }
    return "";
};
