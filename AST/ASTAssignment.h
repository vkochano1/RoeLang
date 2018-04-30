#pragma once

#include <AST/ASTElement.h>

namespace roe
{
    
class ASTAssignment : public ASTElement
{
public:
    ASTAssignment( Context& context
                 , ASTElementPtr left
                 , ASTElementPtr right);

public:
    virtual llvm::Value* evaluate() override;    
    
private:    
    ASTElementPtr left_;
    ASTElementPtr right_;
};

}


