#include <AST/ASTFunctionCall.h>
#include <AST/ASTArgList.h>

#include <FunctionRegistrar.h>

namespace roe
{
    
   const std::string  ASTFunctionCall::TO_STRING_BUILTIN  = "str";
   const std::string  ASTFunctionCall::TO_INT_BUILTIN  = "int";
   
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
        if (name_ == TO_STRING_BUILTIN)
        {
            auto& builder = context_.builder();

            args_->evaluate();

            auto* argList = dynamic_cast<ASTArgList*> (args_.get());
            auto values = argList->values();

            retValue = builder.CreateAlloca(context_.types().stringType());
            values.push_back(retValue);

            if (values[0]->getType() == context_.types().longType())
                FunctionRegistrar::instance().makeCall(context_, StringOps::INT_TO_STR, values);
            else
                FunctionRegistrar::instance().makeCall(context_, StringOps::DOUBLE_TO_STR, values);
            
            return true;
        }
        else if (name_ == TO_INT_BUILTIN)
        {
            auto& builder = context_.builder();

            args_->evaluate();

            auto* argList = dynamic_cast<ASTArgList*> (args_.get());
            auto values = argList->values();

            llvm::Type* firstArg = values[0]->getType();
            
            if(firstArg == context_.types().stringPtrType())
            {
                retValue = FunctionRegistrar::instance().makeCall(context_, StringOps::TO_INT_STR, values);
            }
            else if (firstArg == context_.types().charPtrType())
            {
                retValue = FunctionRegistrar::instance().makeCall(context_, StringOps::TO_INT_CHPTR, values);
            }
            else
            {
                throw ASTException("Invalid str arguments");
            }
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
            throw ASTException("Not a function call");
        }
        
        return value;
    }

}
