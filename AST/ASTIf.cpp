#include <AST/ASTIf.h>

namespace roe
{
    
    ASTIf::ASTIf(Context& context
        , ASTElementPtr condition
        , ASTElementPtr mainBlock
        , ASTElementPtr elseBlock)
   : ASTElement(context)
   , condition_(condition)
   , mainBlock_(mainBlock)
   , elseBlock_(elseBlock)
    {
    }
    
    
    llvm::Value* ASTIf::evaluate()
    {
        auto cond = condition_->evaluate();

        llvm::Value* condExpResult = cond;
        
        auto& builder = context_.builder();
      
        auto* func = context_.rule().funcPtr();
        
        llvm::BasicBlock* ifMain = llvm::BasicBlock::Create(builder.getContext(), "ifMain", func);
        
        llvm::BasicBlock* ifElse = llvm::BasicBlock::Create(builder.getContext(), "ifElse", func);
        
        llvm::BasicBlock* ifEnd = llvm::BasicBlock::Create(builder.getContext(), "IfEnd", func);
    
        builder.CreateCondBr(condExpResult, ifMain, ifElse);
    
        builder.SetInsertPoint(ifMain);
        
        mainBlock_->evaluate();
        
        builder.CreateBr(ifEnd);
    
        builder.SetInsertPoint(ifElse);
        
        elseBlock_->evaluate();
        
        builder.CreateBr(ifEnd);
        
        builder.SetInsertPoint(ifEnd);
                    
        return nullptr;
    }
    
}
