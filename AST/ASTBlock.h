#pragma once

#include <AST/ASTElement.h>

namespace roe
{
  class ASTBlock : public ASTElement
  {
  public:
    ASTBlock(Context& context);
    virtual llvm::Value* evaluate() override;
    void addElement(ASTElementPtr element);

  private:
    ASTElementCollection elements_;
  };
}
