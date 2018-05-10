#include <AST/ASTRule.h>
#include <Module/Context.h>

namespace roe
{

    ASTRule::ASTRule( Context& context
                    , const std::string& ruleID
                    , ASTFunctionParametersPtr params
                    , ASTElementPtr ruleAST)
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
        auto*  entry = llvm::BasicBlock::Create(context_, "entrypoint", context_.rule().funcPtr());
        context_.rule().entryBlock(entry);
        builder.SetInsertPoint(entry);
        ruleAST_->evaluate();
        builder.CreateRetVoid();
    }

    const std::string& ASTRule::name() const
    {
        return ruleID_;
    }

}
