#pragma once
#include <Context.h>
#include <Driver.h>
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
#include <FunctionRegistrar.h>



namespace roe
{

class IContainerAccess;
class Module final
{
public:
    enum class RoeFunctionType : uint8_t
    {
         Unk
      ,  Processor
      ,  Converter
    };

    struct CompiledFunctionInfo
    {
        using ProcessorFuncPtr = void (*)(IContainerAccess*);
        using ConverterFuncPtr = void (*)(IContainerAccess*, IContainerAccess*);

        CompiledFunctionInfo(const std::string& name, llvm::ExecutionEngine* executionEngine)
        {

            fptr_ = reinterpret_cast<void*>(executionEngine->getFunctionAddress(name));
        }

        void call(IContainerAccess* access)
        {
            ProcessorFuncPtr processorPtr = reinterpret_cast<ProcessorFuncPtr>(fptr_);
            processorPtr(access);
        }

        void call(IContainerAccess* from, IContainerAccess* to)
        {
            ConverterFuncPtr converterPtr = reinterpret_cast<ConverterFuncPtr>(fptr_);
            converterPtr(from, to);
        }

        CompiledFunctionInfo()
        {
            fptr_= nullptr;
            type_ = RoeFunctionType::Unk;
        }
    private:
        void* fptr_ ;
        RoeFunctionType type_;
    };

    CompiledFunctionInfo& getFunc(const std::string& funcName)
    {
        return compiledFunctions_[funcName];
    }

    using CompiledFunctions = std::unordered_map<std::string, CompiledFunctionInfo>;

    Module(const std::string& name);
    void compileToIR();
    bool constructAST(const std::string& text);
    void dumpIR();
    void buildNative();
    Context& context() {return context_;};
private:
    Context context_;
    llvm::ExecutionEngine* executionEngine_ = nullptr;
    std::unique_ptr<llvm::EngineBuilder> engineBuilder_;
    llvm::Module* module_ = nullptr;
    CompiledFunctions compiledFunctions_;
    std::unique_ptr<roe::Driver> driver_;
};


}
