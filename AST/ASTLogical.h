#pragma once

#include <AST/ASTElement.h>
#include <Exceptions/ASTException.h>
namespace roe
{

  class ASTLogicalNOT : public ASTElement
  {
  public:
    ASTLogicalNOT(Context& context, ASTElementPtr operand);

  public:
    virtual llvm::Value* evaluate() override;

  private:
    ASTElementPtr operand_;
  };

  class ASTCompare : public ASTElement
  {
  public:
    enum class Operator : uint8_t
    {
      MORE,
      LESS,
      NOT_EQUAL,
      EQUAL,
      MORE_OR_EQUAL,
      LESS_OR_EQUAL
    };

  public:
    ASTCompare(Context& context, Operator op, ASTElementPtr operand1,
               ASTElementPtr operand2);

  public:
    virtual llvm::Value* evaluate() override;
    bool
    handleStringEquals(llvm::Value* v1, llvm::Value* v2, llvm::Value*& out);

  private:
    Operator      op_;
    ASTElementPtr operand1_;
    ASTElementPtr operand2_;
  };

  class ASTLogical : public ASTElement
  {
  public:
    enum class Operator : uint8_t
    {
      AND,
      OR
    };

  public:
    ASTLogical(Context& context, Operator op, ASTElementPtr operand1,
               ASTElementPtr operand2);

  public:
    virtual llvm::Value* evaluate();

  private:
    void normalizeValues(llvm::Value*& v1, llvm::Value*& v2);

  private:
    Operator      op_;
    ASTElementPtr operand1_;
    ASTElementPtr operand2_;
  };
}
