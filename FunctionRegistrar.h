#pragma once 

#include <unordered_map>
#include <vector>
#include <Context.h>
#include <iostream>
#include "llvm/Support/raw_ostream.h"

namespace roe
{
 
class FunctionRegistrar
{
public:
    using ExternalFunction = std::tuple<llvm::Function*, void*>;
    using Arguments  = std::vector<llvm::Value*>;
    using Parameters = std::vector<llvm::Type*>;
    
    static FunctionRegistrar& instance()
    {
        static FunctionRegistrar instance;
        return instance;
    }
    
    FunctionRegistrar()
    {
    }
    
    
    template<typename CTX, typename FPTR>
    void registerExternal(CTX& context, const std::string& name, FPTR* fptr, llvm::Type* ret, std::initializer_list<llvm::Type*> params )
    {
        Parameters parameters (params);
        registerExternal_(context, name, fptr, ret, parameters);
    }
    
    template<typename CTX, typename FPTR, typename Args>
    void registerExternal_(CTX& context, const std::string& name, FPTR* fptr, llvm::Type* ret, const Args& args )
    {
        auto* proto = llvm::FunctionType::get(ret, args, false);
       
        llvm::Function *f = llvm::cast<llvm::Function>(context.module()->getOrInsertFunction(name, proto));
       
        externalFunctions_[name] = ExternalFunction(f, (void*)fptr);
    }
    
    template<typename CTX, typename T>
    llvm::CallInst* makeCall(CTX& context,  const std::string& name, T& args )
    {
        auto& builder = context.builder();
        auto& res = externalFunctions_[name];        
        auto& fptr = std::get<0>(res);
        /*llvm::errs() << "Provided params " << args.size() << "\n";
        for (llvm::Value* value : args)
        {
                llvm::errs() << *value->getType() << "\n";
        }
        
        llvm::errs() << "Needed params\n";
        
        for(auto& arg :  fptr->args())
        {
          llvm::errs() << *arg.getType() << "\n";
        }*/
        
        return  builder.CreateCall(fptr,args);
    }
    
    template <typename CTX>
    llvm::CallInst* makeCall(CTX& context,  const std::string& name, std::initializer_list<llvm::Value*> arg_list)
    {
            Arguments arguments(arg_list);
            return makeCall(context, name, arguments);
    }
    
    template <typename ExecutionEngine>
    void applyGlobalMapping(ExecutionEngine& executionEngine, const std::string& name)
    {
        auto& mapping = externalFunctions_[name];
        executionEngine.addGlobalMapping(std::get<0>(mapping),std::get<1>(mapping));
    }
    
    template <typename ExecutionEngine>
    void addAllMappings(ExecutionEngine& executionEngine)
    {
        for (auto& p : externalFunctions_)
        {
            applyGlobalMapping(executionEngine, p.first);
        }
    }
    
private:
    std::unordered_map<std::string, ExternalFunction> externalFunctions_;
};

    
}
