#include <AST/ASTRules.h>

namespace roe
{

  void ASTRules::addRule(ASTRulePtr rule)
  {
    if (rule->name().empty())
    {
      throw ASTException("Invalid ruleID");
    }

    if(!rules_.insert(std::make_pair(rule->name(), rule)).second)
    {
      throw ASTException("Duplicate rule");
    }
  }

  void ASTRules::evaluate()
  {
    for (auto& ruleEntry : rules_)
    {
      const auto& ruleName = ruleEntry.first;
      auto        rulePtr  = ruleEntry.second;

      rulePtr->context().setCurrentRule(ruleName);
      rulePtr->evaluate();
    }
  }
}
