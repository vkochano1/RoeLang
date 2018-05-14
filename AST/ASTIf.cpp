#include <AST/ASTIf.h>

namespace roe
{

  ASTIf::ASTIf(Context& context, ASTElementPtr condition,
               ASTElementPtr mainBlock, ASTElementPtr elseBlock)
    : ASTElement(context)
    , condition_(condition)
    , mainBlock_(mainBlock)
    , elseBlock_(elseBlock)
  {
  }

  llvm::Value* ASTIf::evaluate()
  {
    auto* condExpResult = condition_->evaluate();

    if (!condExpResult)
    {
      throw ASTException("Expected boolean type and got NULL");
    }

    condExpResult       = loadValueIfNeeded(condExpResult);
    condExpResult       = convertToBool(condExpResult);

    if(!isBool(condExpResult))
    {
      throw ASTException("Expected boolean type");
    }

    auto& builder       = context_.builder();
    auto* func          = context_.rule().funcPtr();

    llvm::BasicBlock* ifMain =
      llvm::BasicBlock::Create(builder.getContext(), "ifMain", func);
    llvm::BasicBlock* ifElse = nullptr;
    llvm::BasicBlock* ifEnd =
      llvm::BasicBlock::Create(builder.getContext(), "IfEnd", func);

    if (elseBlock_)
    {
      ifElse = llvm::BasicBlock::Create(builder.getContext(), "ifElse", func);
      builder.CreateCondBr(condExpResult, ifMain, ifElse);
    }
    else
    {
      builder.CreateCondBr(condExpResult, ifMain, ifEnd);
    }

    builder.SetInsertPoint(ifMain);

    mainBlock_->evaluate();

    builder.CreateBr(ifEnd);

    if (elseBlock_)
    {
      builder.SetInsertPoint(ifElse);
      elseBlock_->evaluate();
      builder.CreateBr(ifEnd);
    }

    builder.SetInsertPoint(ifEnd);

    return nullptr;
  }
}
