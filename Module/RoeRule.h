#pragma once

#include <Functions/Bindings.h>
#include <Module/ForwardDecls.h>
#include <Module/VariableInfo.h>

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace roe
{
  class RoeRule final
  {
  public:
    using Builder                = roe::IRBuilder;
    using ParameterToValue       = std::unordered_map<std::string, llvm::Value*>;
    using ParameterToConstraints = std::unordered_map<std::string, std::shared_ptr<IConstraints>>;
    using DeclaredVariables      = std::unordered_map<std::string, VariableInfo>;
    using FunctionParameters     = std::vector<std::string>;

  public:
    RoeRule(Context& context, const std::string& ruleName, const FunctionParameters& params);

    void init(const std::string& ruleName, const FunctionParameters& params);

    // cached
    Context&        context();
    Builder&        builder();
    llvm::Function* funcPtr();

    // parameters
  public:
    llvm::Value* getParamValue(const std::string& name);
    void bindParameter(const std::string& name, std::shared_ptr<IConstraints> constraints);
    std::shared_ptr<IConstraints> getContainerForParam(const std::string& paramName);
    const FunctionParameters& params() const;

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
    mutable DeclaredVariables declaredVariables_;
    FunctionParameters        params_;
    ParameterToValue          paramToValue_;
    llvm::Function*           function_;
    llvm::BasicBlock*         entry_;
    llvm::BasicBlock*         locals_;
    llvm::BasicBlock*         return_;

    Context&                 context_;
    std::unique_ptr<Builder> builder_;
    ParameterToConstraints   paramToConstraints_;
    std::string              ruleName_;
  };
}
