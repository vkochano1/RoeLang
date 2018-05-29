#pragma once

#include <AST/ASTElement.h>

namespace roe
{
  class ASTArithmetical : public ASTElement
  {
  public:
    enum class Operator : uint8_t
    {
      PLUS,
      MINUS,
      MUL,
      DIV,
      MOD
    };

  public:
    ASTArithmetical(Context& context, Operator op, ASTElementPtr operand1, ASTElementPtr operand2);

  public:
    virtual llvm::Value* evaluate() override;

  private:
    bool processStringConcat(llvm::Value*, llvm::Value*, llvm::Value*& out);
    bool processFloat(llvm::Value*, llvm::Value*, llvm::Value*& out);
    bool processLong(llvm::Value*, llvm::Value*, llvm::Value*& out);

  private:
    Operator      op_;
    ASTElementPtr operand1_;
    ASTElementPtr operand2_;
  };
}
