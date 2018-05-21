#include <Exceptions/ASTException.h>
#include <Functions/FunctionRegistrar.h>
#include <Module/Context.h>
#include <iostream>
#include <llvm/Support/raw_ostream.h>

namespace roe
{

  FunctionRegistrar::FunctionRegistrar(Context& context)
    : context_(context)
  {
  }

  void FunctionRegistrar::registerExternal_(
    const std::string& name, void* fptr, llvm::Type* ret,
    std::initializer_list<llvm::Type*> params)
  {
    Parameters parameters(params);
    registerExternal_(name, fptr, ret, parameters);
  }

  void
  FunctionRegistrar::registerExternal_(const std::string& name, void* fptr,
                                       llvm::Type* ret, const Parameters& args)
  {
    auto*           proto = llvm::FunctionType::get(ret, args, false);
    llvm::Function* f     = llvm::cast<llvm::Function>(
      context_.module()->getOrInsertFunction(name, proto));
    externalFunctions_[name] = ExternalFunction(f, fptr);
  }

  llvm::CallInst*
  FunctionRegistrar::makeCall(const std::string& name, const Arguments& args)
  {
    auto& builder = context_.builder();

    auto fit = externalFunctions_.find(name);
    if (fit == externalFunctions_.end())
    {
      throw ASTException() << "Call for unknown function";
    }

    auto& res  = fit->second;
    auto& fptr = std::get<0>(res);

    size_t idx = 0;
    for (auto& arg : fptr->args())
    {
      if (args[idx++]->getType() != arg.getType())
        throw ASTException() <<  "Parameter/Argument mismatch";
    }

    if (idx < args.size())
      throw ASTException() << "Invalid number of arguments";

    return builder.CreateCall(fptr, args);
  }

  llvm::CallInst*
  FunctionRegistrar::makeCall(const std::string&                  name,
                              std::initializer_list<llvm::Value*> arg_list)
  {
    Arguments arguments(arg_list);
    return makeCall(name, arguments);
  }

  void FunctionRegistrar::applyGlobalMapping(ExecutionEngine&   executionEngine,
                                             const std::string& name)
  {
    auto& mapping = externalFunctions_[name];
    executionEngine.addGlobalMapping(std::get<0>(mapping),
                                     std::get<1>(mapping));
  }

  void FunctionRegistrar::addAllMappings(ExecutionEngine& executionEngine)
  {
    for (auto& p : externalFunctions_)
    {
      applyGlobalMapping(executionEngine, p.first);
    }
  }
}
