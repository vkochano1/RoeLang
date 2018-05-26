#pragma once

#include <Exceptions/ASTException.h>
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
    bool isBool(const llvm::Value*);
    bool isFloat(const llvm::Value*);
    bool isLong(const llvm::Value*);
    bool isString(const llvm::Value*);
    bool isCStr(const llvm::Value*);

    bool isFloatPtr(const llvm::Value*);
    bool isLongPtr(const llvm::Value*);

  protected:
    llvm::Value* allocBool();
    llvm::Value* allocFloat();
    llvm::Value* allocLong();
    llvm::Value* allocString();

  protected:
    Context& context_;
  };

  using ASTElementPtr        = std::shared_ptr<ASTElement>;
  using ASTElementCollection = std::vector<ASTElementPtr>;
}
