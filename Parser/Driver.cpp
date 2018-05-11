
#include <fstream>
#include <sstream>

#include <Parser/Driver.h>
#include <Lexer/Scanner.h>

namespace roe
{

Driver::Driver(Context& context)
    : trace_scanning(false),
      trace_parsing(false),
      context_(context)
{
}

bool Driver::parse_stream(const std::istream& in, const std::string& sname)
{
    streamname = sname;

    Scanner scanner(&in);
    scanner.set_debug(trace_scanning);
    this->lexer = &scanner;

    Parser parser(*this);
    parser.set_debug_level(trace_parsing);
    return (parser.parse() == 0);
}


bool Driver::parse_string(const std::string &input, const std::string& sname)
{
    std::istringstream iss(input);
    return parse_stream(iss, sname);
}

void Driver::error(const class location& l, const std::string& m)
{
    std::cerr << l << ": " << m << std::endl;
}

void Driver::error(const std::string& m)
{
    std::cerr << m << std::endl;
}

}
