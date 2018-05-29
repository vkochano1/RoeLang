#pragma once

#include <AST/ASTElement.h>

namespace roe
{
  class ReturnNotification {};
  
  class ASTReturn : public ASTElement
  {
  public:
    ASTReturn(Context& context);

  public:
    virtual llvm::Value* evaluate() override;
  };
}
