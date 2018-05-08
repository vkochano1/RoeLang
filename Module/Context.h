#pragma once

#include <unordered_map>
#include <unordered_set>

#include <assert.h>

#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <tuple>
#include <Types/Types.h>
#include <iostream>
#include <AST/ASTFunctionParameters.h>

#include <Functions/Bindings.h>

namespace roe
{

class FunctionRegistrar;
class Context;

class VariableInfo
{
public:

  VariableInfo(const std::string& name
             , Context& func
             , const llvm::Type*);

  VariableInfo();

  const std::string& name() const;

  const llvm::Value* value() const {return value_;}
  llvm::Value* value()  {return value_;}
  llvm::Type* type() { return type_;}
  const llvm::Type* type() const  { return type_;}

private:
  std::string   name_;
  llvm::Value*  value_;
  llvm::Type*   type_;
};


class RoeRule
{
public:
     using Builder = llvm::IRBuilder<>;
     using ParameterToValue = std::unordered_map<std::string, llvm::Value*>;
     using ParameterToContainer = std::unordered_map<std::string, std::shared_ptr<IContainerAccess> >;
     using DeclaredVariables = std::unordered_map<std::string, VariableInfo>;

public:


    RoeRule(Context& context
           , const std::string& ruleName
           , const ASTFunctionParameters::Parameters& params);

    Context& context();
    llvm::Value* getParamValue(const std::string& name);
    void init(const std::string& ruleName, const ASTFunctionParameters::Parameters& params);
    Builder& builder();
    llvm::Function* funcPtr() ;
    bool hasVariable(const std::string& name) const;
    VariableInfo& addVariable(const VariableInfo& info);
    VariableInfo& getOrCreateVariable(const std::string& name, const llvm::Type* type);
    VariableInfo& getVariable(const std::string& name) const;

    std::shared_ptr<IContainerAccess> getContainerForParam( const std::string& paramName);
    void bindParameter(const std::string& name, std::shared_ptr<IContainerAccess> container);

public:
    mutable DeclaredVariables declaredVariables_;
    ASTFunctionParameters::Parameters params_;
    ParameterToValue paramToValue_;
    llvm::Function* function_;
    Context& context_;
    std::unique_ptr<Builder > builder_;
    ParameterToContainer paramToContainer_;
    std::string ruleName_;
};




class Context : public llvm::LLVMContext
{
public:
    using Rules = std::unordered_map<std::string, std::shared_ptr<RoeRule> >;
public:
    Context ();
    Context(const Context&) = delete;
    Context& operator = (const Context&) = delete;
    ~Context ();
public:
    using Module = llvm::Module;
    void init(Module* module) { module_ = module;}
    Module* module() {return module_;}

public:
    void setCurrentRule(const std::string& name);
    RoeRule::Builder& builder () {return rule().builder();};
    RoeRule& rule() {return *currentRule_;}
    Rules& rules() { return rules_;}
    Types& types();
    RoeRule& rule(const std::string& name) {return *rules_[name];}
    void addNewRule(const std::string& newRuleName, const ASTFunctionParameters::Parameters& params);
    FunctionRegistrar& externalFunctions();

private:
    Rules rules_;
    std::shared_ptr<RoeRule> currentRule_;
    std::unique_ptr<Types> types_;
    llvm::Module* module_ = nullptr;
    std::unique_ptr<FunctionRegistrar> functionRegistrar_;
};

}
