#include <AST/ASTRule.h>
#include <Module/Context.h>

namespace roe
{
  static const std::string LOCALS_LABEL = "locals";
  static const std::string ENTRY_LABEL  = "entrypoint";

  ASTRule::ASTRule(Context& context, const std::string& ruleID, ASTFunctionParametersPtr params, ASTElementPtr ruleAST)
    : ruleID_(ruleID)
    , context_(context)
    , params_(params)
    , ruleAST_(ruleAST)
  {
    context_.addNewRule(ruleID, params->parameters());
  }

  void ASTRule::evaluate()
  {
    auto& builder = context_.builder();
    auto* locals  = llvm::BasicBlock::Create(context_, LOCALS_LABEL, context_.rule().funcPtr());
    auto* entry   = llvm::BasicBlock::Create(context_, ENTRY_LABEL, context_.rule().funcPtr());
    context_.rule().entryBlock(entry);
    context_.rule().localsBlock(locals);

    builder.SetInsertPoint(entry);
    ruleAST_->evaluate();
    builder.CreateRetVoid();

    builder.SetInsertPoint(locals);
    builder.CreateBr(entry);
  }

  Context& ASTRule::context()
  {
    return context_;
  };

  const std::string& ASTRule::name() const
  {
    return ruleID_;
  }
}
