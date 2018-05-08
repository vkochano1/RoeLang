#pragma once

#include <unordered_map>
#include <vector>
#include <Module/Context.h>


namespace roe
{

class FunctionRegistrar
{
public:
    using ExternalFunction = std::tuple<llvm::Function*, void*>;
    using Arguments  = std::vector<llvm::Value*>;
    using Parameters = std::vector<llvm::Type*>;
    using ExecutionEngine = llvm::ExecutionEngine;

public:
    FunctionRegistrar(Context& context);

public:
    template <typename FPTR>
    void registerExternal(const std::string& name
                        , FPTR fptr
                        , llvm::Type* ret
                        , std::initializer_list<llvm::Type*> params)
    {
      registerExternal_(name, reinterpret_cast<void*>(fptr), ret, params);
    }

    template <typename FPTR>
    void registerExternal(const std::string& name
                        , FPTR fptr
                        , llvm::Type* ret
                        , const Parameters& params)
    {
      registerExternal_(name, reinterpret_cast<void*>(fptr), ret, params);
    }

    void registerExternal_(const std::string& name
                        , void* fptr
                        , llvm::Type* ret
                        , std::initializer_list<llvm::Type*> params);

    void registerExternal_(const std::string& name
                        , void* fptr
                        , llvm::Type* ret
                        , const Parameters& params );

    llvm::CallInst* makeCall(const std::string& name,  const Arguments& args);
    llvm::CallInst* makeCall(const std::string& name, std::initializer_list<llvm::Value*> arg_list);

    void applyGlobalMapping(ExecutionEngine& executionEngine, const std::string& name);
    void addAllMappings(ExecutionEngine& executionEngine);

private:
    std::unordered_map<std::string, ExternalFunction> externalFunctions_;
    Context& context_;
};


}
