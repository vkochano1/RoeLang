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
#include <Types.h>
#include <iostream>
#include <AST/ASTFunctionParameters.h>


namespace roe
{
 
class Context;

class RoeRule
{
public:
     using Builder = llvm::IRBuilder<>;
     using ParameterToValue = std::unordered_map<std::string, llvm::Value*>;
     
     
public:
    RoeRule(Context& context
           , const std::string& ruleName
           , const ASTFunctionParameters::Parameters& params);
    
    Context& context() 
    {
        return context_;
        
    }
    
    llvm::Value* getParamValue(const std::string& name) 
    {
        std::cerr << name << std::endl;
        for (auto t : paramToValue_)
        {
            std::cerr<< "getting " << name << " " << t.first << std::endl;
        }
        return paramToValue_[name];
    }
    
    void init(const std::string& ruleName, const ASTFunctionParameters::Parameters& params);
   
    Builder& builder() 
    {
        return *builder_;
    }
    
    llvm::Function* funcPtr() 
    { 
        return function_;
    }
    
public:
    ASTFunctionParameters::Parameters params_;
    ParameterToValue paramToValue_;
    llvm::Function* function_;
    Context& context_;
    std::unique_ptr<Builder > builder_;
    std::string ruleName_;
};


class VariableInfo
{
public:
  enum class TypeEnum
  {
        String
      , Long
      , Double
  };
  
  VariableInfo(const std::string& name
             , Context& func
             , TypeEnum type);
  
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


class Context : public llvm::LLVMContext
{
public:
    using DeclaredVariables = std::unordered_map<std::string, VariableInfo>;
    using Rules = std::unordered_map<std::string, std::shared_ptr<RoeRule> >;
    using FieldNameToTagMapping = std::unordered_map<std::string, int32_t>; 
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
    bool hasVariable(const std::string& name) const;    
    VariableInfo& addVariable(const VariableInfo& info);
    VariableInfo& getOrCreateVariable(const std::string& name, VariableInfo::TypeEnum);
    VariableInfo& getOrCreateVariable(const std::string& name, const llvm::Type* type);

    void setCurrentRule(const std::string& name);
    
    RoeRule::Builder& builder () {return rule().builder();};
    const std::string& getCachedString(const std::string& value);
    VariableInfo& getVariable(const std::string& name) const;
    RoeRule& rule() {return *currentRule_;}
    Rules& rules() { return rules_;}
    RoeRule& rule(const std::string& name) {return *rules_[name];}
    
    void addNewRule(const std::string& newRuleName, const ASTFunctionParameters::Parameters& params);
    int32_t getTagFromFieldName(const std::string& val)
    {
        return fieldNameToTagMapping_[val];
    }
    
    void setTagFromFieldNameMapping(FieldNameToTagMapping&& mapping)
    {
        fieldNameToTagMapping_.swap(mapping);
    }

private:
    mutable DeclaredVariables declaredVariables_;
    Rules rules_;
    std::shared_ptr<RoeRule> currentRule_;
    llvm::Module* module_ = nullptr;
    FieldNameToTagMapping fieldNameToTagMapping_;
    
};
   
}

