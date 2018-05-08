#include <Module/Context.h>
#include <assert.h>
#include <iostream>
#include <Functions/FunctionRegistrar.h>

namespace roe
{


     VariableInfo::VariableInfo(const std::string& name, Context& context, const llvm::Type* type)
     : name_(name)
     {
        value_ = context.builder().CreateAlloca(const_cast<llvm::Type*>(type));
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

        std::vector<llvm::Type*> funcParams (params.size(), context_.types().voidPtrType());

        llvm::FunctionType* funcType = llvm::FunctionType::get(context_.types().voidType(), funcParams, false);


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

   llvm::Value* RoeRule::getParamValue(const std::string& name)
   {
     return paramToValue_[name];
   }
    void RoeRule::bindParameter(const std::string& name, std::shared_ptr<IContainerAccess> container)
    {
      paramToContainer_[name] = container;
    }

    std::shared_ptr<IContainerAccess> RoeRule::getContainerForParam(const std::string& paramName)
    {
       auto fit = paramToContainer_.find(paramName);
       if (fit == paramToContainer_.end())
          return std::shared_ptr<IContainerAccess>();
       return fit->second;
    }

    VariableInfo& RoeRule::getOrCreateVariable(const std::string& name, const llvm::Type* type)
    {
        if(!hasVariable(name))
        {
            VariableInfo info(name,context_, type);

            return this->addVariable(info);
        }

        return this->getVariable(name);
    }

    const std::string& VariableInfo::name() const
    {
        return name_;
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
       assert(hasVariable(name));
       return declaredVariables_[name];
    }

    bool RoeRule::hasVariable(const std::string& name) const
    {
       return declaredVariables_.find(name) != declaredVariables_.end();
    }
////////////////////////
    Context::Context ()
    {
        types_ = std::make_unique<Types> (*this);
        functionRegistrar_ = std::make_unique<FunctionRegistrar> (*this);
    }

    FunctionRegistrar& Context::externalFunctions()
    {
      return *functionRegistrar_;
    }

    void Context::addNewRule(const std::string& newRuleName
                           , const ASTFunctionParameters::Parameters& params)
    {
        rules_[newRuleName] =  std::make_shared<RoeRule>(*this, newRuleName, params);
    }


    Context::~Context()
    {
    }


    Types& Context::types()
    {
        return *types_;
    }

void Context::setCurrentRule(const std::string& name)
{
    currentRule_ = rules_[name];
}

}
