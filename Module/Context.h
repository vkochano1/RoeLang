#pragma once

#include <unordered_map>
#include <unordered_set>

#include <assert.h>

#include <AST/ASTFunctionParameters.h>
#include <Types/Types.h>
#include <iostream>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <tuple>

#include <Functions/Bindings.h>

namespace roe
{

  class FunctionRegistrar;
  class Context;

  class VariableInfo
  {
  public:
    VariableInfo(const std::string& name, Context& func, const llvm::Type*);

    VariableInfo();

    const std::string& name() const;

    const llvm::Value* value() const { return value_; }
    llvm::Value*       value() { return value_; }
    llvm::Type*        type() { return type_; }
    const llvm::Type*  type() const { return type_; }

  private:
    std::string  name_;
    llvm::Value* value_;
    llvm::Type*  type_;
  };

  class RoeRule final
  {
  public:
    using Builder          = llvm::IRBuilder<>;
    using ParameterToValue = std::unordered_map<std::string, llvm::Value*>;
    using ParameterToContainer =
      std::unordered_map<std::string, std::shared_ptr<IContainerAccess>>;
    using DeclaredVariables = std::unordered_map<std::string, VariableInfo>;

  public:
    RoeRule(Context& context, const std::string& ruleName,
            const ASTFunctionParameters::Parameters& params);

    void init(const std::string&                       ruleName,
              const ASTFunctionParameters::Parameters& params);

    // cached
    Context&        context();
    Builder&        builder();
    llvm::Function* funcPtr();

    // parameters
  public:
    llvm::Value* getParamValue(const std::string& name);
    void bindParameter(
      const std::string& name, std::shared_ptr<IContainerAccess> container);
    std::shared_ptr<IContainerAccess>
    getContainerForParam(const std::string& paramName);
    const ASTFunctionParameters::Parameters& params() const { return params_; }

    // local variable
  public:
    bool hasVariable(const std::string& name) const;
    VariableInfo& addVariable(const VariableInfo& info);
    VariableInfo&
    getOrCreateVariable(const std::string& name, const llvm::Type* type);
    VariableInfo& getVariable(const std::string& name) const;

  public:
    // exec block
    llvm::BasicBlock* entryBlock();
    void entryBlock(llvm::BasicBlock* eb);
    // place to insert all local variables
    llvm::BasicBlock* localsBlock();
    void localsBlock(llvm::BasicBlock* lb);

  private:
    mutable DeclaredVariables         declaredVariables_;
    ASTFunctionParameters::Parameters params_;
    ParameterToValue                  paramToValue_;
    llvm::Function*                   function_;
    llvm::BasicBlock*                 entry_;
    llvm::BasicBlock*                 locals_;
    Context&                          context_;
    std::unique_ptr<Builder>          builder_;
    ParameterToContainer              paramToContainer_;
    std::string                       ruleName_;
  };

  class Context final : public llvm::LLVMContext
  {
  public:
    using Rules  = std::unordered_map<std::string, std::shared_ptr<RoeRule>>;
    using Module = llvm::Module;

  public:
    Context();
    Context(const Context&) = delete;
    Context& operator=(const Context&) = delete;
    ~Context();

    void init(Module* module);

  public:
    Module*  module();
    RoeRule& rule();
    Rules&   rules();
    RoeRule& rule(const std::string& name);
    Types&            types();
    RoeRule::Builder& builder();

  public:
    void addNewRule(const std::string&                       newRuleName,
                    const ASTFunctionParameters::Parameters& params);
    void setCurrentRule(const std::string& name);
    FunctionRegistrar& externalFunctions();

  private:
    Rules                              rules_;
    std::shared_ptr<RoeRule>           currentRule_;
    std::unique_ptr<Types>             types_;
    llvm::Module*                      module_ = nullptr;
    std::unique_ptr<FunctionRegistrar> functionRegistrar_;
  };
}
