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
    bool processContainerField(const std::string& fullVarName);
    llvm::Value* evaluateField();
    llvm::Value* evaluateLocalVar();
    
private:
   std::string var_; 
   std::string baseName_;
   bool isField_;
   int32_t tag_;
};

}

