#include <RoeLangLib/Loader.h>
#include <Parser/Driver.h>

#include <fstream>
#include <sstream>
#include <iterator>
#include <thread>

#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>

namespace roe
{
  std::once_flag initFlag;

  Loader::Loader()
  {
    std::call_once(initFlag, []() {
      llvm::InitializeNativeTarget();
      llvm::InitializeNativeTargetAsmParser();
      llvm::InitializeNativeTargetAsmPrinter();
    });
  }
  std::shared_ptr<Module> Loader::tryLoadModule(const std::string& name, const std::string& text)
  {
    std::istringstream in(text);
    return tryLoadModule_(name, in);
  }

  ModulePtr Loader::tryLoadModule_(const std::string& name, const std::istream& in)
  {
    auto module = std::make_shared<roe::Module>(name);
    if (!module->constructAST(in))
    {
      std::ostringstream ostrm;
      ostrm << "Failed to build AST from source" << module->errorText();
      throw std::runtime_error(ostrm.str());
    }

    modules_[name] = module;
    return module;
  }

  void Loader::buildAll()
  {
    for (const auto& moduleMapping : modules_)
    {
      moduleMapping.second->buildNative();
    }
  }

  void Loader::dumpAll(std::ostream& ostrm)
  {
    for (const auto& moduleMapping : modules_)
    {
      ostrm << "Module : " << moduleMapping.first << std::endl;

      moduleMapping.second->dumpIR(ostrm);

      ostrm << std::endl;
    }
  }

  ModulePtr Loader::tryLoadModuleFromFile(const std::string& name, const std::string& path)
  {
    std::ifstream in(path.c_str());
    return tryLoadModule_(name, in);
  }

  Module::CompiledFunctionInfo Loader::getCompiledFunction(const std::string& moduleName, std::string& functionName)
  {
    auto fit = modules_.find(moduleName);

    if (fit == modules_.end())
      throw std::runtime_error("Module not found");

    return fit->second->function(functionName);
  }
}
