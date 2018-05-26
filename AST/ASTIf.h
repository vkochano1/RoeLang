#pragma once

#include <AST/ASTElement.h>

namespace roe
{
  class ASTIf : public ASTElement
  {
  public:
    ASTIf(Context& context, ASTElementPtr condition, ASTElementPtr mainBlock, ASTElementPtr elseBlock);

  public:
    virtual llvm::Value* evaluate() override;

  public:
    ASTElementPtr condition_;
    ASTElementPtr mainBlock_;
    ASTElementPtr elseBlock_;
  };
}
