#pragma once

#include <AST/ASTRule.h>
#include <unordered_map>

namespace roe
{

  class ASTRules
  {
  public:
    using RuleContainer = std::unordered_map<std::string, ASTRulePtr>;

    void addRule(ASTRulePtr rule);
    void evaluate();

  private:
    RuleContainer rules_;
  };
}
