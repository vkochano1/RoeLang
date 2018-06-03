#include <Module/ForwardDeclsImpl.h>

#include <AST/ASTElement.h>
#include <AST/ASTReturn.h>
#include <Exceptions/ASTException.h>
#include <Module/Context.h>
#include <Module/Module.h>
#include <Module/RoeRule.h>

namespace roe
{
  RoeRule::RoeRule(Context& context, const std::string& ruleName, const FunctionParameters& params)
    : context_(context)
    , ruleName_(ruleName)
  {
    params_ = params;
    init(ruleName_, params);
  }

  const RoeRule::FunctionParameters& RoeRule::params() const
  {
    return params_;
  }

  void RoeRule::init(const std::string& ruleID, const FunctionParameters& params)
  {
    builder_.reset(new Builder(context_.native()));

    std::vector<llvm::Type*> funcParams(params.size(), context_.types().voidPtrType());

    llvm::FunctionType* funcType = llvm::FunctionType::get(context_.types().voidType(), funcParams, false);

    function_ =
      llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, ruleID, context_.module()->nativeModule());

    auto paramsIt = params.begin();
    for (auto& arg : function_->args())
    {
      paramToValue_[*paramsIt] = &arg;
      ++paramsIt;
    }
  }

  llvm::Value* RoeRule::getParamValue(const std::string& name)
  {
    auto fit = paramToValue_.find(name);
    if (fit == paramToValue_.end())
    {
      throw ASTException() << "Unknown function parameter " << name;
    }
    return fit->second;
  }

  void RoeRule::bindParameter(const std::string& name, std::shared_ptr<IConstraints> constraints)
  {
    auto insertRes = paramToConstraints_.insert(std::make_pair(name, constraints));
    if (insertRes.second == false)
    {
      throw ASTException() << "Duplicate parameter bindings";
    }
  }

  std::shared_ptr<IConstraints> RoeRule::getContainerForParam(const std::string& paramName)
  {
    auto fit = paramToConstraints_.find(paramName);
    if (fit == paramToConstraints_.end())
      return std::shared_ptr<IConstraints>();
    return fit->second;
  }

  VariableInfo& RoeRule::getOrCreateVariable(const std::string& name, const llvm::Type* type)
  {
    if (!hasVariable(name))
    {
      VariableInfo info(name, context_, type);

      return this->addVariable(info);
    }

    return this->getVariable(name);
  }

  llvm::BasicBlock* RoeRule::entryBlock()
  {
    return entry_;
  }

  void RoeRule::entryBlock(llvm::BasicBlock* eb)
  {
    entry_ = eb;
  }

  llvm::BasicBlock* RoeRule::localsBlock()
  {
    return locals_;
  }

  void RoeRule::localsBlock(llvm::BasicBlock* lb)
  {
    locals_ = lb;
  }

  VariableInfo& RoeRule::addVariable(const VariableInfo& info)
  {
    assert(!hasVariable(info.name()));
    declaredVariables_[info.name()] = info;
    return declaredVariables_[info.name()];
  }

  RoeRule::Builder& RoeRule::builder()
  {
    return *builder_;
  }

  llvm::Function* RoeRule::funcPtr()
  {
    return function_;
  }

  VariableInfo& RoeRule::getVariable(const std::string& name) const
  {
    if (!hasVariable(name))
      throw ASTException() << "Unknown variable";

    return declaredVariables_[name];
  }

  bool RoeRule::hasVariable(const std::string& name) const
  {
    return declaredVariables_.find(name) != declaredVariables_.end();
  }
}
