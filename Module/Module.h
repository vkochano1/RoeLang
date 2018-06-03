#pragma once

#include <Functions/FunctionRegistrar.h>
#include <Module/Context.h>
#include <memory>

namespace roe
{
  class IContainerAccess;
  class Driver;

  class Module final
  {
  public:
    struct CompiledFunctionInfo
    {
      CompiledFunctionInfo(const std::string& name, size_t nParams, llvm::ExecutionEngine* executionEngine);

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

    Module::CompiledFunctionInfo& function(const std::string& funcName);
    CompiledFunctions& functions();

    void compileToIR();
    bool constructAST(const std::string& text);
    bool constructAST(const std::istream& text);
    llvm::Module* nativeModule();

    void bindParamsConstraints(
      const std::string& functionName, std::initializer_list<std::shared_ptr<IConstraints>> constraints);

    void dumpIR(std::ostream& ostrm);
    void        buildNative();
    std::string errorText() const;

  private:
    llvm::ExecutionEngine*               executionEngine_;
    Context                              context_;
    llvm::Module*                        module_;
    CompiledFunctions                    compiledFunctions_;
    std::unique_ptr<roe::Driver>         driver_;
    std::unique_ptr<llvm::EngineBuilder> engineBuilder_;
    std::string                          compilationError_;
    bool                                 compiled_;
  };

  using ModulePtr = std::shared_ptr<Module>;
}
