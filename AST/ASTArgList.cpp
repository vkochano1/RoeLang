#include <AST/ASTArgList.h>
#include <AST/ASTVariable.h>

namespace roe
{
  ASTArgList::ASTArgList(Context& context)
    : ASTElement(context)
  {
  }

  void ASTArgList::addArgument(ASTElementPtr arg)
  {
    auto variablePtr = std::dynamic_pointer_cast<ASTVariable>(arg);
    if (variablePtr)
    {
      variableArguments_.push_back(variablePtr->name());
    }
    else
    {
      variableArguments_.push_back("");
    }

    args_.push_back(arg);
  }

  const ASTArgList::VariableArguments& ASTArgList::variableArguments() const
  {
    return variableArguments_;
  }

  size_t ASTArgList::size() const
  {
    return args_.size();
  }

  llvm::Value* ASTArgList::evaluate()
  {
    for (auto& arg : args_)
    {
      auto* val = arg->evaluate();
      val       = loadValueIfNeeded(val);
      values_.push_back(val);
    }

    return nullptr;
  }

  const ASTArgList::EvaluatedValues& ASTArgList::values() const
  {
    return values_;
  }
}
