#include <iostream>
#include "driver.hh"

int main (int argc, char *argv[])
{
    int res = 1;
    driver drv;
    for (int i = 1; i < argc - 1; ++i)
    {
        if (argv[i] == std::string ("-p"))
        {
            drv.trace_parsing = true;
        }
        else
        {
            if (argv[i] == std::string ("-l"))
            {
                drv.trace_scanning = true;
            }
            else
            {
                if (i == argc - 1)
                {
                    res = 2;
                }
                res = 0;
                if (!drv.parse(argv[i]))
                {
                    drv.result.print(argv[i + 1]);
                }
            }
        }
    }
    if (res == 1)
    {
        std::cerr << "No input file\n";
    }
    if (res == 2)
    {
        std::cerr << "No output file\n";
    }
    return res;
}
