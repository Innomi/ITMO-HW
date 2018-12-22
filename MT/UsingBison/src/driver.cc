#include "driver.hh"
#include "prefcalc.hh"

driver::driver ()
  : trace_parsing(false), trace_scanning(false)
{};

int driver::parse(const std::string & in)
{
    in_file = in;
    location.initialize(&in_file);
    scan_begin();
    yy::parser parse(*this);
    parse.set_debug_level(trace_parsing);
    int res = parse();
    scan_end();
    return res;
};
