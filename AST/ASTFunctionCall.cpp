#include <AST/ASTFunctionCall.h>
#include <AST/ASTArgList.h>

#include <FunctionRegistrar.h>

namespace roe
{
   
   ASTFunctionCall::ASTFunctionCall(Context& context
    , const std::string& name, ASTElementPtr  args)
    : ASTElement(context)
     , name_(name) 
     , args_(args)
    {
    }
    
    ASTFunctionCall::~ASTFunctionCall()
    {
    }
    
    llvm::Value* ASTFunctionCall::processBuiltins()
    {
        if (name_ == "str")
        {
            auto& builder = context_.builder();
            this->args_->evaluate();
            auto* argList = dynamic_cast<ASTArgList*> (this->args_.get());
            auto values = argList->values();
            auto* ret = builder.CreateAlloca(Types::instance().stringType());
            values.push_back(ret);
            FunctionRegistrar::instance().makeCall(context_, "str", values);
            return ret;
        }
        
        return nullptr;
    }
    
    llvm::Value* ASTFunctionCall::evaluate()
    {
        auto& builder = context_.builder();
        
        auto fit = context_.rules().find(name_);
        if(fit != context_.rules().end())
        {
            auto& rule = *fit->second;
            llvm::Value* arg1 = rule.funcPtr()->arg_begin();
            return  builder.CreateCall(rule.funcPtr(), {arg1});   
        }
        
        llvm::Value* ret = processBuiltins();
        if (ret)
        {
            return ret;
        }
        
        this->args_->evaluate();
        auto* argList = dynamic_cast<ASTArgList*> (this->args_.get());
        auto& values = argList->values();
        
        return FunctionRegistrar::instance().makeCall(context_, this->name_, values);
    }

}
