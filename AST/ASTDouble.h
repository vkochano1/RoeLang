#pragma once

#include <AST/ASTElement.h>

namespace roe
{

  class ASTDouble : public ASTElement
  {
  public:
    ASTDouble(Context& context, double value);

  public:
    virtual llvm::Value* evaluate() override;

  private:
    double value_;
  };
}
