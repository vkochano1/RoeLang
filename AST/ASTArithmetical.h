#pragma once

#include <AST/ASTElement.h>

namespace roe
{

class ASTArithmetical : public ASTElement
{
public:
    enum class Operator
    {
        PLUS,
        MINUS,
        MUL,
        DIV
    };
public:
    ASTArithmetical(Context& context, Operator op, ASTElementPtr op1, ASTElementPtr op2);
    virtual llvm::Value* evaluate();
private:
   Operator op_; 
   ASTElementPtr operand1_;
   ASTElementPtr operand2_;
};

}

