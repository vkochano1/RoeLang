#pragma once

#include <string>
#include <vector>
#include <Context.h>
#include <AST/ASTElements.h>
#include <AST/ASTRules.h>


namespace roe 
{

class Driver
{
public:
    /// construct a new parser driver context
    Driver(Context& context);

    bool trace_scanning;
    bool trace_parsing;
    std::string streamname;
    bool parse_stream(std::istream& in,
		      const std::string& sname = "stream input");
    bool parse_string(const std::string& input,
		      const std::string& sname = "string stream");


    void error(const class location& l, const std::string& m);
    void error(const std::string& m);
    class Scanner* lexer;
    Context& context() {return context_;}
    ASTRules& rules() {return astRules_;}
public:
    Context& context_;
    roe::ASTRules astRules_;

};

} 
