#pragma once

#include <AST/ASTElement.h>

namespace roe
{

class ASTVariable: public ASTElement
{
protected:
    static const std::string TAG_PREFIX;
    static const std::string FIELD_PREFIX;
public:
    ASTVariable(Context& context, const std::string& var);

public:
    virtual llvm::Value* evaluate() override;

public:
    const std::string& name () const;
    const std::string& baseName() const;
    bool isField() const;
    size_t tag() const;

private:
    bool processContainerField();
    llvm::Value* evaluateField();
    llvm::Value* evaluateLocalVar();

private:
   std::string var_;
   std::string baseName_;
   std::string fieldName_;
   bool isField_;
   int64_t tag_;
};

using ASTVariablePtr = std::shared_ptr<ASTVariable>;

}
