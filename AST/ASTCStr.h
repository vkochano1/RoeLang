#pragma once

#include <AST/ASTElement.h>

namespace roe
{
  class ASTCstr : public ASTElement
  {
  public:
    ASTCstr(Context& context, const std::string& v);

  public:
    virtual llvm::Value* evaluate() override;
    llvm::Value*         length() const;

  private:
    std::string value_;
  };
}
