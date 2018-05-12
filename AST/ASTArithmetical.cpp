#include <AST/ASTArithmetical.h>
#include <Functions/FunctionRegistrar.h>
#include <Functions/StringOps.h>

namespace roe
{
  ASTArithmetical::ASTArithmetical(Context& context, Operator op,
                                   ASTElementPtr op1, ASTElementPtr op2)
    : ASTElement(context)
    , op_(op)
    , operand1_(op1)
    , operand2_(op2)
  {
  }

  bool
  ASTArithmetical::processStringConcat(llvm::Value* left, llvm::Value* right,
                                       llvm::Value*& out)
  {
    auto& builder = context_.builder();

    out = nullptr;

    if (left->getType() == context_.types().stringPtrType() &&
        right->getType() == context_.types().stringPtrType())
    {
      out = builder.CreateAlloca(context_.types().stringType());
      context_.externalFunctions().makeCall(StringOps::CONCAT_STR_AND_STR,
                                            {left, left, right});
    }
    else if (left->getType() == context_.types().stringPtrType() &&
             right->getType() == context_.types().charPtrType())
    {
      out = builder.CreateAlloca(context_.types().stringType());
      context_.externalFunctions().makeCall(StringOps::CONCAT_STR_AND_CHPTR,
                                            {left, right, out});
    }
    else if (left->getType() == context_.types().charPtrType() &&
             right->getType() == context_.types().stringPtrType())
    {
      out = builder.CreateAlloca(context_.types().stringType());
      context_.externalFunctions().makeCall(StringOps::CONCAT_CHPTR_AND_STR,
                                            {left, right, out});
    }
    else if (left->getType() == context_.types().charPtrType() &&
             right->getType() == context_.types().charPtrType())
    {
      out = builder.CreateAlloca(context_.types().stringType());
      context_.externalFunctions().makeCall(StringOps::CONCAT_CHPTR_AND_CHPTR,
                                            {left, right, out});
    }

    return out != nullptr;
  }

  bool ASTArithmetical::processLong(llvm::Value* left, llvm::Value* right,
                                    llvm::Value*& out)
  {
    auto& builder = context_.builder();
    if (left->getType() == context_.types().longType())
    {
      switch (op_)
      {
        case Operator::PLUS:
          out = builder.CreateAdd(left, right);
          break;
        case Operator::MINUS:
          out = builder.CreateSub(left, right);
          break;
        case Operator::MUL:
          out = builder.CreateMul(left, right);
          break;
        case Operator::DIV:
          out = builder.CreateExactSDiv(left, right);
          break;
      };
    }
  }

  bool ASTArithmetical::processFloat(llvm::Value* left, llvm::Value* right,
                                     llvm::Value*& out)
  {
    auto& builder = context_.builder();
    if (left->getType() == context_.types().floatType())
    {
      switch (op_)
      {
        case Operator::PLUS:
          out = builder.CreateFAdd(left, right);
          break;
        case Operator::MINUS:
          out = builder.CreateFSub(left, right);
          break;
        case Operator::MUL:
          out = builder.CreateFMul(left, right);
          break;
        case Operator::DIV:
          out = builder.CreateFDiv(left, right);
          break;
      };
    }
  }

  llvm::Value* ASTArithmetical::evaluate()
  {
    auto& builder = context_.builder();

    auto left  = operand1_->evaluate();
    auto right = operand2_->evaluate();

    left  = loadValueIfNeeded(left);
    right = loadValueIfNeeded(right);

    normalizeValues(left, right);

    llvm::Value* out = nullptr;

    if (processStringConcat(left, right, out) ||
        processFloat(left, right, out) || processLong(left, right, out))
    {
      return out;
    }

    throw ASTException("Incompatible arguments");
  }
}
