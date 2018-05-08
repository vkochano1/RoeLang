
#pragma once

#include <map>
#include <vector>
#include <ostream>
#include <stdexcept>
#include <cmath>
#include <iostream>
//#include <boost/variant.hpp>

#include <Module/Context.h>
#include <AST/ASTElements.h>
#include <AST/ASTRule.h>


namespace roe
{

struct YYSTYPE
{
    long  			longVal_;
    std::string     stringVal_;
    double          doubleVal_;
    ASTElementPtr   astElement_;
    ASTRulePtr      astRule_;
    ASTFunctionParametersPtr astParameters_;
};

}
