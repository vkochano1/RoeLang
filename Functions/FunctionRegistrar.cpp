#include <Functions/FunctionRegistrar.h>
#include <iostream>
#include <llvm/Support/raw_ostream.h>
#include <Module/Context.h>


namespace roe
{

  FunctionRegistrar::FunctionRegistrar(Context& context)
    : context_(context)
  {
  }

  void FunctionRegistrar::registerExternal_(const std::string& name, void* fptr, llvm::Type* ret, std::initializer_list<llvm::Type*> params )
  {
      Parameters parameters (params);
      registerExternal_(name, fptr, ret, parameters);
  }

  void FunctionRegistrar::registerExternal_(const std::string& name, void* fptr, llvm::Type* ret, const Parameters& args )
  {
      auto* proto = llvm::FunctionType::get(ret, args, false);
      llvm::Function *f = llvm::cast<llvm::Function>(context_.module()->getOrInsertFunction(name, proto));
      externalFunctions_[name] = ExternalFunction(f, fptr);
  }

  llvm::CallInst* FunctionRegistrar::makeCall(const std::string& name,  const Arguments& args )
  {
      auto& builder = context_.builder();
      auto& res = externalFunctions_[name];
      auto& fptr = std::get<0>(res);
      llvm::errs() << "Provided params " << args.size() << "\n";
      for (llvm::Value* value : args)
      {
              llvm::errs() << *value->getType() << "\n";
      }

      llvm::errs() << "Needed params\n";

      for(auto& arg :  fptr->args())
      {
        llvm::errs() << *arg.getType() << "\n";
      }

      return  builder.CreateCall(fptr,args);
  }

  llvm::CallInst* FunctionRegistrar::makeCall(const std::string& name, std::initializer_list<llvm::Value*> arg_list)
  {
          Arguments arguments(arg_list);
          return makeCall(name, arguments);
  }

  void FunctionRegistrar::applyGlobalMapping(ExecutionEngine& executionEngine, const std::string& name)
  {
      auto& mapping = externalFunctions_[name];
      executionEngine.addGlobalMapping(std::get<0>(mapping),std::get<1>(mapping));
  }

  void FunctionRegistrar::addAllMappings(ExecutionEngine& executionEngine)
  {
      for (auto& p : externalFunctions_)
      {
          applyGlobalMapping(executionEngine, p.first);
      }
  }

}
