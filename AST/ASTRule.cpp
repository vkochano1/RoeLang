#include <AST/ASTRule.h>
#include <Context.h>

namespace roe
{

    ASTRule::ASTRule( Context& context
                    , const std::string& ruleID
                    , ASTFunctionParametersPtr params
                    , ASTElement::ASTElementPtr ruleAST)
    : ruleID_ (ruleID)
    , context_(context)
    , params_ (params)
    , ruleAST_(ruleAST)
    {
        
        context_.addNewRule(ruleID, params->parameters());
    }
    
    void ASTRule::evaluate()
    {
        auto& builder = context_.builder();
        
        auto  entry = llvm::BasicBlock::Create(context_, "entrypoint", context_.rule().funcPtr());
        
        builder.SetInsertPoint(entry);
        
        ruleAST_->evaluate();
       
        builder.CreateRet(llvm::ConstantInt::get(builder.getContext(), llvm::APInt(32, 0)));
    }
    
    const std::string& ASTRule::name() const
    {
        return ruleID_;
    }

}
