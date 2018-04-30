
#pragma once

#include <AST/ASTElement.h>

namespace roe
{

class ASTLogicalNOT : public ASTElement
{
public:
    ASTLogicalNOT(Context& context, ASTElementPtr op1);
    virtual llvm::Value* evaluate() override;
private:
   ASTElementPtr operand1_;
};


class ASTCompare : public ASTElement
{
public:
    enum class Operator
    {
        MORE,
        LESS,
        NOT_EQUAL,
        EQUAL,
        MORE_OR_EQUAL,
        LESS_OR_EQUAL
    };
public:
    ASTCompare(Context& context, Operator op, ASTElementPtr operand1, ASTElementPtr operand2);
    virtual llvm::Value* evaluate() override;
private:
   Operator op_; 
   ASTElementPtr operand1_;
   ASTElementPtr operand2_;
};

class ASTLogical : public ASTElement
{
public:
    enum class Operator
    {
        AND,
        OR
    };
public:
    ASTLogical(Context& context, Operator op, ASTElementPtr operand1, ASTElementPtr operand2);
    virtual llvm::Value* evaluate();
private:
   Operator op_; 
   ASTElementPtr operand1_;
   ASTElementPtr operand2_;
};

}
