#pragma once

#include <AST/ASTArgList.h>
#include <AST/ASTElement.h>
#include <AST/ASTFunctionParameters.h>

namespace roe
{

  class Context;

  class ASTRule
  {
  public:
    ASTRule(Context& context, const std::string& ruleID,
            ASTFunctionParametersPtr params, ASTElementPtr ruleAST);
    void               evaluate();
    const std::string& name() const;
    Context&           context() { return context_; };

  private:
    std::string              ruleID_;
    Context&                 context_;
    ASTElementPtr            ruleAST_;
    ASTFunctionParametersPtr params_;
  };

  using ASTRulePtr = std::shared_ptr<ASTRule>;
}
