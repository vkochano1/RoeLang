#include <Context.h>
#include <assert.h>
#include <iostream>
#include <FunctionRegistrar.h>

namespace roe
{
    
     VariableInfo::VariableInfo(const std::string& name, Context& context, TypeEnum type)
     : name_(name)
     {
                  
         switch(type)
         {
              case TypeEnum::String:
                    value_ = context.builder().CreateAlloca(Types::instance().stringType());
              break;
              case TypeEnum::Long:
                    value_ = context.builder().CreateAlloca(Types::instance().longType());
              break;

         };
     }
     
     VariableInfo::VariableInfo(const std::string& name, Context& context, const llvm::Type* type)
     : name_(name)
     {
        value_ = context.builder().CreateAlloca((llvm::Type* )type);
     }
  
    VariableInfo::VariableInfo()
    {
      
    }
  
    RoeRule::RoeRule(Context& context, const std::string& ruleName, const ASTFunctionParameters::Parameters& params)
        : context_  (context)
        , ruleName_ (ruleName)
    {
        params_ = params;
        init(ruleName_, params);
    }
    
    void RoeRule::init(const std::string& ruleID, const ASTFunctionParameters::Parameters& params)
    {
        builder_.reset(new Builder(context_));

        std::vector<llvm::Type*> funcParams (params.size(), Types::instance().voidPtrType());
        
        llvm::FunctionType* funcType = llvm::FunctionType::get(Types::instance().longType(), funcParams, false);	
        
        
        function_ = llvm::Function::Create(funcType
                                       , llvm::Function::ExternalLinkage
                                       , ruleID
                                       , context_.module());
    
        auto paramsIt = params.begin();
        for (auto& arg : function_->args())
        {
            paramToValue_[*paramsIt] = &arg;
            std::cerr << *paramsIt << std::endl;
            ++paramsIt;
        }
    }

    const std::string& VariableInfo::name() const
    {
        return name_;
    }

    Context::Context () 
    {
    }
    
    void Context::addNewRule(const std::string& newRuleName
                           , const ASTFunctionParameters::Parameters& params)
    {
        rules_[newRuleName] =  std::make_shared<RoeRule>(*this, newRuleName, params);
    }
    
    
    Context::~Context()
    {
    }
    
    VariableInfo& Context::getOrCreateVariable(const std::string& name, VariableInfo::TypeEnum type)
    {
        if(!this->hasVariable(name))
        {   
            VariableInfo info(name, *this, type);
            
            return this->addVariable(info);
        }
        
        return this->getVariable(name);
    }
    
    VariableInfo& Context::getOrCreateVariable(const std::string& name, const llvm::Type* type)
    {
        if(!this->hasVariable(name))
        {   
            VariableInfo info(name, *this, type);
            
            return this->addVariable(info);
        }
        
        return this->getVariable(name);
    }
        
    VariableInfo& Context::addVariable(const VariableInfo& info)
    {
       assert(!hasVariable(info.name()));
       declaredVariables_[info.name()] = info;
       return declaredVariables_[info.name()];
    }
    
    VariableInfo& Context::getVariable(const std::string& name) const 
    {
       assert(hasVariable(name));
       return declaredVariables_[name];
    }
    
    bool Context::hasVariable(const std::string& name) const 
    {
       return declaredVariables_.find(name) != declaredVariables_.end();
    }
    
        

void Context::setCurrentRule(const std::string& name)
{
    currentRule_ = rules_[name];
}

}

