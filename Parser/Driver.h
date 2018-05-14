#pragma once

#include <AST/ASTElements.h>
#include <AST/ASTRules.h>
#include <Module/Context.h>
#include <string>
#include <vector>
#include <sstream>

namespace roe
{

  class Driver
  {
  public:
    /// construct a new parser driver context
    Driver(Context& context);

    bool        trace_scanning;
    bool        trace_parsing;
    std::string streamname;
    bool parse_stream(const std::istream& in,
                      const std::string&  sname = "stream input");
    bool parse_string(const std::string& input,
                      const std::string& sname = "string stream");

    void error(const class location& l, const std::string& m);
    void error(const std::string& m);
    class Scanner* lexer;
    Context&       context() { return context_; }
    ASTRules&      rules() { return astRules_; }

    std::string errorText() const;
  public:
    Context&      context_;
    roe::ASTRules astRules_;
    std::ostringstream   error_;
  };
}
