#include <AST/ASTArgList.h>
#include <AST/ASTFunctionCall.h>

#include <Functions/FunctionRegistrar.h>

namespace roe
{
  const std::string ASTFunctionCall::TO_STRING_BUILTIN = "str";
  const std::string ASTFunctionCall::TO_INT_BUILTIN    = "int";
  const std::string ASTFunctionCall::TO_DOUBLE_BUILTIN = "double";
  const std::string ASTFunctionCall::PRINT_BUILTIN     = "print";
  const std::string ASTFunctionCall::LENGTH_BUILTIN    = "len";

  ASTFunctionCall::ASTFunctionCall(Context& context, const std::string& name, ASTElementPtr args)
    : ASTElement(context)
    , name_(name)
    , args_(args)
  {
  }

  ASTFunctionCall::~ASTFunctionCall()
  {
  }

  bool ASTFunctionCall::isBuiltInFunction() const
  {
    return name_ == TO_STRING_BUILTIN || name_ == TO_DOUBLE_BUILTIN || name_ == TO_INT_BUILTIN ||
           name_ == PRINT_BUILTIN || name_ == LENGTH_BUILTIN;
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
      throw ASTException() << "Invalid ASTElement, expected arg list";
    }
    auto values = argList->values();
    if (values.size() < 1)
    {
      throw ASTException() << "Invalid number of arguments";
    }

    auto* firstArg = values[0];

    if (name_ == TO_STRING_BUILTIN)
    {
      if (isString(firstArg))
      {
        retValue = values[0];
        return true;
      }
      retValue = allocString();
      values.push_back(retValue);

      if (isLong(firstArg))
      {
        context_.externalFunctions().makeCall(StringOps::INT_TO_STR, values);
      }
      else if (isFloat(firstArg))
      {
        context_.externalFunctions().makeCall(StringOps::DOUBLE_TO_STR, values);
      }
      else
      {
        throw ASTException() << "Invalid argument for str function";
      }
      return true;
    }
    else if (name_ == TO_INT_BUILTIN)
    {
      if (isString(firstArg))
      {
        retValue = context_.externalFunctions().makeCall(StringOps::TO_INT_STR, values);
      }
      else if (isCStr(firstArg))
      {
        retValue = context_.externalFunctions().makeCall(StringOps::TO_INT_CHPTR, values);
      }
      else if (isFloat(firstArg))
      {
        retValue = context_.externalFunctions().makeCall(StringOps::DOUBLE_TO_INT, values);
      }
      else
      {
        throw ASTException() << "Invalid str arguments";
      }
      return true;
    }
    else if (name_ == TO_DOUBLE_BUILTIN)
    {
      if (isString(firstArg))
      {
        retValue = context_.externalFunctions().makeCall(StringOps::TO_DOUBLE_STR, values);
      }
      else if (isCStr(firstArg))
      {
        retValue = context_.externalFunctions().makeCall(StringOps::TO_DOUBLE_CHPTR, values);
      }
      else
      {
        throw ASTException() << "Invalid str arguments";
      }
      return true;
    }
    else if (name_ == PRINT_BUILTIN)
    {
      //!!!! todo I32
      int64_t printer = reinterpret_cast<int64_t>(context_.printer());
      if (!printer)
      {
        throw ASTException() << "Printer is not set";
      }

      llvm::Value* printerVal = llvm::ConstantInt::get(context_.types().longType(), printer);
      values.insert(values.begin(), printerVal);

      if (isString(firstArg))
      {
        context_.externalFunctions().makeCall(Bindings::PRINT_STR, values);
      }
      else if (isLong(firstArg))
      {
        context_.externalFunctions().makeCall(Bindings::PRINT_INT, values);
      }
      else if (isFloat(firstArg))
      {
        context_.externalFunctions().makeCall(Bindings::PRINT_DOUBLE, values);
      }
      else if (isCStr(firstArg))
      {
        context_.externalFunctions().makeCall(Bindings::PRINT_CSTR, values);
      }
      else
      {
        throw ASTException() << "Invalid print arguments";
      }
      return true;
    }
    else if (name_ == LENGTH_BUILTIN)
    {
      if (isString(firstArg))
      {
        retValue = context_.externalFunctions().makeCall(StringOps::GET_LENGTH, values);
      }
      else
      {
        throw ASTException() << "Invalid length argument";
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
      throw ASTException() << "Exepected ASTArgList";
    }

    if (argList->variableArguments().size() != rule.funcPtr()->arg_size())
    {
      throw ASTException() << "Invalid number of arguments";
    }

    std::vector<llvm::Value*> args;
    for (const auto& argName : argList->variableArguments())
    {
      if (argName.empty())
      {
        throw ASTException() << "Invalid non-var argument";
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
      throw ASTException() << "Expected ASTArgList";
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
      throw ASTException() << "Not a function call";
    }

    return value;
  }
}
