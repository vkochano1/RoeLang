#pragma once

#include <AST/ASTElement.h>

namespace roe
{

  class ASTArgList : public ASTElement
  {
  public:
    using Arguments         = std::vector<ASTElementPtr>;
    using EvaluatedValues   = std::vector<llvm::Value*>;
    using VariableArguments = std::vector<std::string>;

  public:
    ASTArgList(Context& context);

  public:
    virtual llvm::Value*     evaluate() override;
    const VariableArguments& variableArguments() const;

  public:
    void addArgument(ASTElementPtr arg);
    const EvaluatedValues& values() const;
    size_t                 size() const;

  private:
    Arguments         args_;
    EvaluatedValues   values_;
    VariableArguments variableArguments_;
  };

  using ASTArgListPtr = std::shared_ptr<ASTArgList>;
}
