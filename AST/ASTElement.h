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
    virtual ~ASTElement();

  public:
    ASTElement& operator=(const ASTElement&);
    ASTElement(const ASTElement&);

  public:
    virtual llvm::Value* evaluate() = 0;

  protected:
    void normalizeValues(llvm::Value*& v1, llvm::Value*& v2);
    llvm::Value* loadValueIfNeeded(llvm::Value* value);
    llvm::Value* convertToBool(llvm::Value* v);

  protected:
    Context& context_;
  };

  using ASTElementPtr        = std::shared_ptr<ASTElement>;
  using ASTElementCollection = std::vector<ASTElementPtr>;
}
