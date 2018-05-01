#include <AST/ASTFunctionCall.h>
#include <AST/ASTArgList.h>

#include <FunctionRegistrar.h>

namespace roe
{
   
   ASTFunctionCall::ASTFunctionCall(Context& context
                                    , const std::string& name
                                    , ASTElementPtr  args)
                                    : ASTElement(context)
                                    , name_(name) 
                                    , args_(args)
    {
    }
    
    ASTFunctionCall::~ASTFunctionCall()
    {
    }
    
    bool ASTFunctionCall::processBuiltins(llvm::Value*& retValue)
    {
        if (name_ == "str")
        {
            auto& builder = context_.builder();

            args_->evaluate();

            auto* argList = dynamic_cast<ASTArgList*> (args_.get());
            auto values = argList->values();

            retValue = builder.CreateAlloca(Types::instance().stringType());
            values.push_back(retValue);

            FunctionRegistrar::instance().makeCall(context_, "str", values);

            return true;
        }
        
        return false;
    }
 
    bool ASTFunctionCall::processModuleFunction(llvm::Value*& retValue)
    {
        auto& builder = context_.builder();
        
        auto fit = context_.rules().find(name_);
        
        if(fit != context_.rules().end())
        {
            auto& rule = *fit->second;
            
            std::vector<llvm::Value*> args;
            for (auto& arg : rule.funcPtr()->args())
            {
                    args.push_back(&arg);
            }
            
            retValue = builder.CreateCall(rule.funcPtr(), args);  
            return true;
        }
        return false;
    }
    
    bool ASTFunctionCall::processRegularFunction(llvm::Value*& retValue)
    {
        args_->evaluate();
        
        auto* argList = dynamic_cast<ASTArgList*> (args_.get());
        auto& values = argList->values();
        
        retValue =  FunctionRegistrar::instance().makeCall(context_, name_, values);
        
        return true;
    }
    
    llvm::Value* ASTFunctionCall::evaluate()
    {
        llvm::Value* value = nullptr;
        
        bool processed = processModuleFunction(value);
        
        if (!processed)
        {
            processed = processBuiltins(value);
        }
        
        if (!processed)
        {
            processed = processRegularFunction(value);
        }
        
        if(!processed)
        {
            throw std::logic_error("Call failed");
        }
        
        return value;
    }

}
