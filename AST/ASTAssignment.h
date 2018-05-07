#pragma once

#include <AST/ASTElement.h>

namespace roe
{

class ASTVariable;

class ASTAssignment : public ASTElement
{
public:
    ASTAssignment( Context& context
                 , ASTElementPtr left
                 , ASTElementPtr right);

public:
    virtual llvm::Value* evaluate() override;   
    
private:
    void processAssignmentToField(const ASTVariable& var, llvm::Value* to, llvm::Value* from);
    void processAssignmentToLocalStrVar(const ASTVariable& var, llvm::Value* to, llvm::Value* from);
    void processAssignmentToLocalIntVar(const ASTVariable& var, llvm::Value* to, llvm::Value* from);
    void processAssignmentToLocalFloatVar(const ASTVariable& var, llvm::Value* to, llvm::Value* from);
private:    
    ASTElementPtr left_;
    ASTElementPtr right_;
};

}


