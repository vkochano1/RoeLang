#include <AST/ASTArithmetical.h>
#include <AST/ASTCStr.h>
#include <Functions/FunctionRegistrar.h>
#include <Functions/StringOps.h>
#include <llvm/IR/IRBuilder.h>

namespace roe
{
  ASTArithmetical::ASTArithmetical(Context& context, Operator op, ASTElementPtr op1, ASTElementPtr op2)
    : ASTElement(context)
    , op_(op)
    , operand1_(op1)
    , operand2_(op2)
  {
  }

  bool ASTArithmetical::processStringConcat(llvm::Value* left, llvm::Value* right, llvm::Value*& out)
  {
    out = nullptr;

    if (isString(left) && isString(right))
    {
      out = allocString();
      context_.externalFunctions().makeCall(StringOps::CONCAT_STR_AND_STR, {left, right, out});
    }
    else if (isString(left) && isCStr(right))
    {
      out          = allocString();
      auto astCStr = std::dynamic_pointer_cast<ASTCstr>(operand2_);
      context_.externalFunctions().makeCall(StringOps::CONCAT_STR_AND_CHPTR, {left, right, astCStr->length(), out});
    }
    else if (isCStr(left) && isString(right))
    {
      out          = allocString();
      auto astCStr = std::dynamic_pointer_cast<ASTCstr>(operand1_);
      context_.externalFunctions().makeCall(StringOps::CONCAT_CHPTR_AND_STR, {left, astCStr->length(), right, out});
    }
    else if (isCStr(left) && isCStr(right))
    {
      out               = allocString();
      auto astCStrLeft  = std::dynamic_pointer_cast<ASTCstr>(operand1_);
      auto astCStrRight = std::dynamic_pointer_cast<ASTCstr>(operand2_);
      context_.externalFunctions().makeCall(
        StringOps::CONCAT_CHPTR_AND_CHPTR, {left, astCStrLeft->length(), right, astCStrRight->length(), out});
    }

    return out != nullptr;
  }

  bool ASTArithmetical::processLong(llvm::Value* left, llvm::Value* right, llvm::Value*& out)
  {
    auto& builder = context_.builder();
    out           = nullptr;

    if (isLong(left))
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
        case Operator::MOD:
          out = builder.CreateSRem(left, right);
          break;
        default:
          throw((ASTException()) << "Opearand is not supported");
          break;
      };
    }
    return out != nullptr;
  }

  bool ASTArithmetical::processFloat(llvm::Value* left, llvm::Value* right, llvm::Value*& out)
  {
    auto& builder = context_.builder();
    out           = nullptr;

    if (isFloat(left))
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
        default:
          throw ASTException() << "Opearand is not supported";
          break;
      };
    }
    return out != nullptr;
  }

  llvm::Value* ASTArithmetical::evaluate()
  {
    auto  left    = operand1_->evaluate();
    auto  right   = operand2_->evaluate();

    left  = loadValueIfNeeded(left);
    right = loadValueIfNeeded(right);

    normalizeValues(left, right);

    llvm::Value* out = nullptr;
    if (processStringConcat(left, right, out) || processFloat(left, right, out) || processLong(left, right, out))
    {
      return out;
    }

    throw ASTException() << "Incompatible arguments";
  }
}
