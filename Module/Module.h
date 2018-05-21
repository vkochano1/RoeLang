#pragma once

#include <Module/Context.h>
#include <Parser/Driver.h>
#include <memory>

#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/MCJIT.h>

#include <Functions/FunctionRegistrar.h>

namespace roe
{

  class IContainerAccess;
  class Module final
  {

  public:
    struct CompiledFunctionInfo
    {
      CompiledFunctionInfo(const std::string& name, size_t nParams,
                           llvm::ExecutionEngine* executionEngine);

      template<typename... T>
      void call(T*... args)
      {
        using FptrT = void (*)(T * ...);
        FptrT f     = reinterpret_cast<FptrT>(fptr_);

        if (sizeof...(args) != nParams_)
        {
          throw std::logic_error("Number of arguments mismatch");
        }

        f(args...);
      }

      CompiledFunctionInfo();

    private:
      void*  fptr_;
      size_t nParams_;
    };

  public:
    using CompiledFunctions = std::unordered_map<std::string, CompiledFunctionInfo>;

  public:
    Module(const std::string& name);
    Context& context();

    Module::CompiledFunctionInfo& getFunc(const std::string& funcName);

    void compileToIR();
    bool constructAST(const std::string& text);
    bool constructAST(const std::istream& text);

    void bindFunctionParameterConstraints
    (
      const std::string& functionName,
      std::initializer_list<std::shared_ptr<IConstraints>> constraints
    );

    void     dumpIR(std::ostream& ostrm);
    void     buildNative();
    std::string errorText() const;

  private:
    llvm::ExecutionEngine*               executionEngine_;
    Context                              context_;
    std::unique_ptr<llvm::EngineBuilder> engineBuilder_;
    llvm::Module*                        module_;
    CompiledFunctions                    compiledFunctions_;
    std::unique_ptr<roe::Driver>         driver_;
    std::string compilationError_;
    bool compiled_;
  };

  using ModulePtr = std::shared_ptr<Module>;
}
