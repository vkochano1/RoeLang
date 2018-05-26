#pragma once

#include <AST/ASTFunctionParameters.h>
#include <Functions/Bindings.h>
#include <Module/VariableInfo.h>

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>

#include <unordered_map>
#include <unordered_set>

namespace roe
{
  class RoeRule final
  {
  public:
    using Builder                = llvm::IRBuilder<>;
    using ParameterToValue       = std::unordered_map<std::string, llvm::Value*>;
    using ParameterToConstraints = std::unordered_map<std::string, std::shared_ptr<IConstraints>>;
    using DeclaredVariables      = std::unordered_map<std::string, VariableInfo>;

  public:
    RoeRule(Context& context, const std::string& ruleName, const ASTFunctionParameters::Parameters& params);

    void init(const std::string& ruleName, const ASTFunctionParameters::Parameters& params);

    // cached
    Context&        context();
    Builder&        builder();
    llvm::Function* funcPtr();

    // parameters
  public:
    llvm::Value* getParamValue(const std::string& name);
    void bindParameter(const std::string& name, std::shared_ptr<IConstraints> constraints);
    std::shared_ptr<IConstraints> getContainerForParam(const std::string& paramName);
    const ASTFunctionParameters::Parameters& params() const;

    // local variable
  public:
    bool hasVariable(const std::string& name) const;
    VariableInfo& addVariable(const VariableInfo& info);
    VariableInfo& getOrCreateVariable(const std::string& name, const llvm::Type* type);
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
    ParameterToConstraints            paramToConstraints_;
    std::string                       ruleName_;
  };
}
