#pragma once

#include <AST/ASTException.h>
#include <Module/Context.h>
#include <llvm/IR/DerivedTypes.h>

namespace roe
{
  class ASTElement
  {
  public:
    ASTElement(Context& context);

  public:
    virtual llvm::Value* evaluate() = 0;
    virtual ~ASTElement(){};

  protected:
    void normalizeValues(llvm::Value*& v1, llvm::Value*& v2);
    llvm::Value* loadValueIfNeeded(llvm::Value* value);

  protected:
    Context& context_;
  };

  using ASTElementPtr        = std::shared_ptr<ASTElement>;
  using ASTElementCollection = std::vector<ASTElementPtr>;
}
