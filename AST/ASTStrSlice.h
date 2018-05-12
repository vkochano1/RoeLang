#pragma once

#include <AST/ASTElement.h>
#include <AST/ASTVariable.h>

namespace roe
{

  class ASTStrSlice : public ASTElement
  {
  public:
    ASTStrSlice(Context& context, ASTElementPtr base, ASTElementPtr from,
                ASTElementPtr len);

    virtual llvm::Value* evaluate() override;

  private:
    ASTElementPtr base_;
    ASTElementPtr from_;
    ASTElementPtr len_;
  };
}
