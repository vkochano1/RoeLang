#include <AST/ASTLogical.h>
#include <Functions/FunctionRegistrar.h>
#include <AST/ASTCStr.h>

namespace roe
{

  ASTLogical::ASTLogical(Context&      context,
                         Operator      op,
                         ASTElementPtr op1,
                         ASTElementPtr op2)
    : ASTElement(context)
    , op_(op)
    , operand1_(op1)
    , operand2_(op2)
  {
  }

  llvm::Value* ASTLogical::evaluate()
  {
    auto& builder = context_.builder();

    auto v1 = operand1_->evaluate();
    auto v2 = operand2_->evaluate();

    v1 = loadValueIfNeeded(v1);
    v2 = loadValueIfNeeded(v2);

    normalizeValues(v1, v2);

    llvm::Value* out = nullptr;
    switch (op_)
    {
      case Operator::AND:
        out = builder.CreateAnd(v1, v2);
        break;
      case Operator::OR:
        out = builder.CreateOr(v1, v2);
        break;
      defualt:
        throw ASTException("Invalid arguments for logical expression");
        break;
    };

    return out;
  }

  void ASTLogical::normalizeValues(llvm::Value*& v1, llvm::Value*& v2)
  {
    v1 = convertToBool(v1);
    v2 = convertToBool(v2);

    if (!isBool(v2) || !isBool(v2))
    {
      throw ASTException("Failed to convert to bool");
    }
  }

  ASTLogicalNOT::ASTLogicalNOT(Context& context, ASTElementPtr operand)
    : ASTElement(context)
    , operand_(operand)
  {
  }

  llvm::Value* ASTLogicalNOT::evaluate()
  {
    auto& builder = context_.builder();
    auto* value   = operand_->evaluate();
    value         = loadValueIfNeeded(value);
    value         = convertToBool(value);

    if (!isBool(value))
    {
      throw ASTException("Failed to convert to bool");
    }

    return builder.CreateNot(value);
  }

  ASTCompare::ASTCompare(Context&      context,
                         Operator      op,
                         ASTElementPtr op1,
                         ASTElementPtr op2)
    : ASTElement(context)
    , op_(op)
    , operand1_(op1)
    , operand2_(op2)
  {
  }

  bool ASTCompare::handleStringEquals(llvm::Value*  v1,
                                      llvm::Value*  v2,
                                      llvm::Value*& out)
  {
    out = nullptr;

    if (v1->getType() == context_.types().stringPtrType() &&
        v2->getType() == context_.types().stringPtrType())
    {
      out = context_.externalFunctions().makeCall(StringOps::EQUALS_STR_AND_STR,
                                                  {v1, v2});
      return true;
    }
    else if (v1->getType() == context_.types().charPtrType() &&
             v2->getType() == context_.types().stringPtrType())
    {
      auto astCStrLeft =  std::dynamic_pointer_cast<ASTCstr> (operand1_);
      out = context_.externalFunctions().makeCall(
        StringOps::EQUALS_CHPTR_AND_STR, {v1, astCStrLeft->length(), v2});
      return true;
    }
    else if (v1->getType() == context_.types().stringPtrType() &&
             v2->getType() == context_.types().charPtrType())
    {
      auto astCStr =  std::dynamic_pointer_cast<ASTCstr> (operand2_);
      out = context_.externalFunctions().makeCall(
        StringOps::EQUALS_STR_AND_CHPTR, {v1, v2, astCStr->length() });
      return true;
    }
    else if (v1->getType() == context_.types().charPtrType() &&
             v2->getType() == context_.types().charPtrType())
    {
      auto astCStrLeft =  std::dynamic_pointer_cast<ASTCstr> (operand1_);
      auto astCStrRight =  std::dynamic_pointer_cast<ASTCstr> (operand2_);

      out = context_.externalFunctions().makeCall(
        StringOps::EQUALS_CHPTR_AND_CHPTR, {v1,astCStrLeft->length(), v2, astCStrRight->length()});
      return true;
    }

    return false;
  }

  llvm::Value* ASTCompare::evaluate()
  {
    auto& builder = context_.builder();

    auto v1 = operand1_->evaluate();
    auto v2 = operand2_->evaluate();

    if (!(v1 && v2))
    {
      throw ASTException("Invalid value(s) for comaparison");
    }

    v1 = loadValueIfNeeded(v1);
    v2 = loadValueIfNeeded(v2);

    normalizeValues(v1, v2);

    llvm::Value* out = nullptr;
    switch (op_)
    {
      case Operator::LESS:
      {
        if (v1->getType() == context_.types().floatType())
        {
          out = builder.CreateFCmpOLT(v1, v2);
        }
        else
        {
          out = builder.CreateICmpSLT(v1, v2);
        }
      }
      break;
      case Operator::MORE:
        out = builder.CreateICmpSGT(v1, v2);
        break;
      case Operator::EQUAL:
      {
        if (!handleStringEquals(v1, v2, /*in-out*/ out))
        {
          out = builder.CreateICmpEQ(v1, v2);
        }
      }
      break;
      case Operator::NOT_EQUAL:
      {
        if (handleStringEquals(v1, v2, /*in-out*/ out))
        {
          out = builder.CreateNot(out);
        }
        else
        {
          out = builder.CreateICmpNE(v1, v2);
        }
      }
      break;
      case Operator::MORE_OR_EQUAL:
        out = builder.CreateICmpSGE(v1, v2);
        break;
      case Operator::LESS_OR_EQUAL:
        out = builder.CreateICmpSLE(v1, v2);
        break;
    };

    return out;
  }
}
