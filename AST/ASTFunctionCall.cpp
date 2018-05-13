#include <AST/ASTArgList.h>
#include <AST/ASTFunctionCall.h>

#include <Functions/FunctionRegistrar.h>

namespace roe
{

  const std::string ASTFunctionCall::TO_STRING_BUILTIN = "str";
  const std::string ASTFunctionCall::TO_INT_BUILTIN    = "int";
  const std::string ASTFunctionCall::PRINT_BUILTIN     = "print";

  ASTFunctionCall::ASTFunctionCall(Context& context, const std::string& name,
                                   ASTElementPtr args)
    : ASTElement(context)
    , name_(name)
    , args_(args)
  {
  }

  ASTFunctionCall::~ASTFunctionCall() {}

  bool ASTFunctionCall::isBuiltInFunction() const
  {
    return name_ == TO_STRING_BUILTIN || name_ == TO_INT_BUILTIN ||
           name_ == PRINT_BUILTIN;
  }

  bool ASTFunctionCall::processBuiltins(llvm::Value*& retValue)
  {
    if (!isBuiltInFunction())
    {
      return false;
    }

    auto& builder = context_.builder();
    args_->evaluate();

    auto argList = std::dynamic_pointer_cast<ASTArgList>(args_);
    if (!argList)
    {
      throw ASTException("Invalid ASTElement, expected arg list");
    }
    auto values = argList->values();
    if (values.size() < 1)
    {
      throw ASTException("Invalid number of arguments");
    }

    llvm::Type* firstArgType = values[0]->getType();

    if (name_ == TO_STRING_BUILTIN)
    {
      if (firstArgType == context_.types().stringPtrType())
      {
        retValue = values[0];
        return true;
      }
      retValue = builder.CreateAlloca(context_.types().stringType());
      values.push_back(retValue);

      if (firstArgType == context_.types().longType())
      {
        context_.externalFunctions().makeCall(StringOps::INT_TO_STR, values);
      }
      else if (firstArgType == context_.types().floatType())
      {
        context_.externalFunctions().makeCall(StringOps::DOUBLE_TO_STR, values);
      }
      else
      {
        throw ASTException("Invalid argument for str function");
      }
      return true;
    }
    else if (name_ == TO_INT_BUILTIN)
    {
      if (firstArgType == context_.types().stringPtrType())
      {
        retValue =
          context_.externalFunctions().makeCall(StringOps::TO_INT_STR, values);
      }
      else if (firstArgType == context_.types().charPtrType())
      {
        retValue = context_.externalFunctions().makeCall(
          StringOps::TO_INT_CHPTR, values);
      }
      else
      {
        throw ASTException("Invalid str arguments");
      }
      return true;
    }
    else if (name_ == PRINT_BUILTIN)
    {
      if (firstArgType == context_.types().stringPtrType())
      {
        context_.externalFunctions().makeCall(Bindings::PRINT_STR, values);
      }
      else if (firstArgType == context_.types().longType())
      {
        context_.externalFunctions().makeCall(Bindings::PRINT_INT, values);
      }
      else if (firstArgType == context_.types().floatType())
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
    auto  fit     = context_.rules().find(name_);

    if (fit == context_.rules().end())
      return false;

    auto& rule = *fit->second;

    auto argList = std::dynamic_pointer_cast<ASTArgList>(args_);

    if (!argList)
    {
      throw ASTException("Exepected ASTArgList");
    }

    if (argList->variableArguments().size() != rule.funcPtr()->arg_size())
    {
      throw ASTException("Invalid number of arguments");
    }

    std::vector<llvm::Value*> args;
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

  bool ASTFunctionCall::processRegularFunction(llvm::Value*& retValue)
  {
    args_->evaluate();
    auto argList = std::dynamic_pointer_cast<ASTArgList>(args_);
    if (!argList)
    {
      throw ASTException("Expected ASTArgList");
    }
    auto& values = argList->values();
    retValue     = context_.externalFunctions().makeCall(name_, values);
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

    if (!processed)
    {
      throw ASTException("Not a function call");
    }

    return value;
  }
}
