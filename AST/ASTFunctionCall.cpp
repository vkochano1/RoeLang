#include <AST/ASTFunctionCall.h>
#include <AST/ASTArgList.h>

#include <Functions/FunctionRegistrar.h>

namespace roe
{

   const std::string  ASTFunctionCall::TO_STRING_BUILTIN  = "str";
   const std::string  ASTFunctionCall::TO_INT_BUILTIN  = "int";
   const std::string  ASTFunctionCall::PRINT_BUILTIN  = "print";


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
                context_.externalFunctions().makeCall(StringOps::INT_TO_STR, values);
            else
                context_.externalFunctions().makeCall(StringOps::DOUBLE_TO_STR, values);

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
                retValue = context_.externalFunctions().makeCall(StringOps::TO_INT_STR, values);
            }
            else if (firstArg == context_.types().charPtrType())
            {
                retValue = context_.externalFunctions().makeCall(StringOps::TO_INT_CHPTR, values);
            }
            else
            {
                throw ASTException("Invalid str arguments");
            }
            return true;
        }
        else if (name_ == PRINT_BUILTIN)
        {
          auto& builder = context_.builder();

          args_->evaluate();

          auto* argList = dynamic_cast<ASTArgList*> (args_.get());
          auto values = argList->values();

          llvm::Type* firstArg = values[0]->getType();

          if(firstArg == context_.types().stringPtrType())
          {
              context_.externalFunctions().makeCall(Bindings::PRINT_STR, values);
          }
          else if (firstArg == context_.types().longType())
          {
            context_.externalFunctions().makeCall(Bindings::PRINT_INT, values);
          }
          else if (firstArg == context_.types().floatType())
          {
            context_.externalFunctions().makeCall(Bindings::PRINT_DOUBLE, values);
          }
          else
          {
              throw ASTException("Invalid print arguments");
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
            auto* argList = dynamic_cast<ASTArgList*> (args_.get());

            if (argList->variableArguments().size() != rule.funcPtr()->arg_size())
            {
              throw ASTException("Invalid number of arguments");
            }

            for (const auto& argName : argList->variableArguments())
            {
                if (argName.empty())
                {
                      throw ASTException("Invalid non-var argument");
                }

                llvm::Value* container = context_.rule().getParamValue(argName);
                args.push_back(container);
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
        retValue =  context_.externalFunctions().makeCall(name_, values);
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
