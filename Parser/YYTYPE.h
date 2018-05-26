
#pragma once

#include <cmath>
#include <iostream>
#include <map>
#include <ostream>
#include <stdexcept>
#include <vector>
//#include <boost/variant.hpp>

#include <AST/ASTElements.h>
#include <AST/ASTRule.h>
#include <Module/Context.h>

namespace roe
{
  struct YYSTYPE
  {
    long                     longVal_;
    std::string              stringVal_;
    double                   doubleVal_;
    ASTElementPtr            astElement_;
    ASTRulePtr               astRule_;
    ASTFunctionParametersPtr astParameters_;
  };
}
