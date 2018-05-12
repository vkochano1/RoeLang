#include <AST/ASTRules.h>

namespace roe
{

  void ASTRules::addRule(ASTRulePtr rule) { rules_[rule->name()] = rule; }

  void ASTRules::evaluate()
  {
    for (auto& rule : rules_)
    {
      rule.second->context().setCurrentRule(rule.first);
      rule.second->evaluate();
    }
  }
}
