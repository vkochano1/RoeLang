#include <Exceptions/ASTException.h>
#include <Functions/FunctionRegistrar.h>
#include <Module/Context.h>
#include <assert.h>
#include <iostream>

namespace roe
{

  VariableInfo::VariableInfo(const std::string& name, Context& context,
                             const llvm::Type* type)
    : name_(name)
  {
    auto* cur = context.builder().GetInsertBlock();
    context.builder().SetInsertPoint(context.rule().localsBlock());
    value_ = context.builder().CreateAlloca(const_cast<llvm::Type*>(type));
    context.builder().SetInsertPoint(cur);
  }

  VariableInfo::VariableInfo() {}

  RoeRule::RoeRule(Context& context, const std::string& ruleName,
                   const ASTFunctionParameters::Parameters& params)
    : context_(context)
    , ruleName_(ruleName)
  {
    params_ = params;
    init(ruleName_, params);
  }

  void RoeRule::init(const std::string&                       ruleID,
                     const ASTFunctionParameters::Parameters& params)
  {
    builder_.reset(new Builder(context_));

    std::vector<llvm::Type*> funcParams(params.size(),
                                        context_.types().voidPtrType());

    llvm::FunctionType* funcType =
      llvm::FunctionType::get(context_.types().voidType(), funcParams, false);

    function_ = llvm::Function::Create(
      funcType, llvm::Function::ExternalLinkage, ruleID, context_.module());

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
      throw ASTException() << "Unknown function parameter";
    }
    return fit->second;
  }

  void RoeRule::bindParameter(
    const std::string& name, std::shared_ptr<IConstraints> constraints)
  {
    auto insertRes = paramToConstraints_.insert(std::make_pair(name, constraints));
    if (insertRes.second == false)
    {
      throw ASTException() << "Duplicate parameter bindings";
    }
  }

  std::shared_ptr<IConstraints>
  RoeRule::getContainerForParam(const std::string& paramName)
  {
    auto fit = paramToConstraints_.find(paramName);
    if (fit == paramToConstraints_.end())
      return std::shared_ptr<IConstraints>();
    return fit->second;
  }

  VariableInfo&
  RoeRule::getOrCreateVariable(const std::string& name, const llvm::Type* type)
  {
    if (!hasVariable(name))
    {
      VariableInfo info(name, context_, type);

      return this->addVariable(info);
    }

    return this->getVariable(name);
  }

  const std::string& VariableInfo::name() const { return name_; }

  VariableInfo& RoeRule::addVariable(const VariableInfo& info)
  {
    assert(!hasVariable(info.name()));
    declaredVariables_[info.name()] = info;
    return declaredVariables_[info.name()];
  }

  RoeRule::Builder& RoeRule::builder() { return *builder_; }

  llvm::Function* RoeRule::funcPtr() { return function_; }

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
  ////////////////////////
  Context::Context()
  {
    types_             = std::make_unique<Types>(*this);
    functionRegistrar_ = std::make_unique<FunctionRegistrar>(*this);
  }

  FunctionRegistrar& Context::externalFunctions()
  {
    return *functionRegistrar_;
  }

  void Context::addNewRule(const std::string&                       newRuleName,
                           const ASTFunctionParameters::Parameters& params)
  {
    auto rule = std::make_shared<RoeRule>(*this, newRuleName, params);
    auto rit  = rules_.insert(std::make_pair(newRuleName, rule));
    if (rit.second == false)
    {
      throw ASTException() << "Duplicate rule";
    }
  }

  void Context::init(Module* module) { module_ = module; }

  RoeRule& Context::rule(const std::string& name) { return *rules_[name]; }

  Context::~Context() {}

  Types& Context::types() { return *types_; }

  llvm::BasicBlock* RoeRule::entryBlock() { return entry_; }

  void RoeRule::entryBlock(llvm::BasicBlock* eb) { entry_ = eb; }

  llvm::BasicBlock* RoeRule::localsBlock() { return locals_; }

  void RoeRule::localsBlock(llvm::BasicBlock* lb) { locals_ = lb; }

  void Context::setCurrentRule(const std::string& name)
  {
    auto fit = rules_.find(name);
    if (fit == rules_.end())
    {
      throw ASTException() << "Unknonw rule";
    }
    currentRule_ = fit->second;
  }

  Context::Module* Context::module() { return module_; }

  RoeRule& Context::rule() { return *currentRule_; }

  Context::Rules& Context::rules() { return rules_; }

  RoeRule::Builder& Context::builder() { return rule().builder(); };
}
