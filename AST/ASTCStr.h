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
    const std::string&   originalValue() const; 

  private:
    std::string value_;
    std::string originalValue_;
  };
}
