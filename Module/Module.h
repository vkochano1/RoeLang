#pragma once

#include <Module/Context.h>
#include <Parser/Driver.h>
#include <memory>

#include "llvm/IR/IRBuilder.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/Support/TargetSelect.h"
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"

#include <Functions/FunctionRegistrar.h>



namespace roe
{

class IContainerAccess;
class Module final
{
public:
    struct CompiledFunctionInfo
    {

        CompiledFunctionInfo(const std::string& name
                            , size_t nParams
                            , llvm::ExecutionEngine* executionEngine)
        {
            nParams_ = nParams;
            fptr_ = reinterpret_cast<void*>(executionEngine->getFunctionAddress(name));
        }

        template <typename... T>
        void call(T*... args)
        {
            using FptrT = void (*) (T*...);
            FptrT f = reinterpret_cast<FptrT> (fptr_);

            if(sizeof...(args)!= nParams_)
            {
               throw std::logic_error("Number of arguments mismatch");
            }

            f(args...);
        }

        CompiledFunctionInfo()
        {
            fptr_= nullptr;
            nParams_ = 0;
        }
    private:
        void* fptr_ ;
        size_t nParams_;
    };

    CompiledFunctionInfo& getFunc(const std::string& funcName)
    {
        return compiledFunctions_[funcName];
    }

    using CompiledFunctions = std::unordered_map<std::string, CompiledFunctionInfo>;

    Module(const std::string& name);

    void compileToIR();
    bool constructAST(const std::string& text);
    bool constructAST(const std::istream& text);
    void bindFunctionParameterConstrains(const std::string& functionName
                                        ,std::initializer_list<std::shared_ptr<IContainerAccess> > accessList);

    void dumpIR();
    void buildNative();
    Context& context() {return context_;};

private:
    llvm::ExecutionEngine* executionEngine_ = nullptr;
    Context context_;
    std::unique_ptr<llvm::EngineBuilder> engineBuilder_;
    llvm::Module* module_ = nullptr;
    CompiledFunctions compiledFunctions_;
    std::unique_ptr<roe::Driver> driver_;
};


}
