#include <Functions/Bindings.h>
#include <Module/Module.h>
#include <llvm/Transforms/IPO/PassManagerBuilder.h>
#include <llvm/Transforms/IPO.h>
#include  <llvm/IR/LegacyPassManager.h>

namespace roe
{

  Module::CompiledFunctionInfo::CompiledFunctionInfo(
    const std::string& name, size_t nParams,
    llvm::ExecutionEngine* executionEngine)
  {
    nParams_ = nParams;
    fptr_ = reinterpret_cast<void*>(executionEngine->getFunctionAddress(name));
  }
  Module::CompiledFunctionInfo::CompiledFunctionInfo()
  {
    fptr_    = nullptr;
    nParams_ = 0;
  }

  Context& Module::context() { return context_; }

  Module::CompiledFunctionInfo& Module::getFunc(const std::string& funcName)

  {
    return compiledFunctions_[funcName];
  }

  Module::Module(const std::string& name)
  {
    compiled_ = false;

    {
      auto module    = std::make_unique<llvm::Module>(name, context_);
      module_        = module.get();
      engineBuilder_ = std::make_unique<llvm::EngineBuilder>(std::move(module));
      executionEngine_ = engineBuilder_->create();
    }

    context_.init(module_);

    roe::StringOps::registerBuiltins(context_);
    roe::Bindings::registerBuiltins(context_);

    driver_ = std::make_unique<roe::Driver>(context_);
  }

  void Module::bindFunctionParameterConstraints(
    const std::string& functionName,
    std::initializer_list<std::shared_ptr<IConstraints>>
      constraintsList)
  {
    auto& roeRule = context().rule(functionName);
    auto  argIt   = constraintsList.begin();

    for (const auto& param : roeRule.params())
    {
      if (argIt == constraintsList.end())
      {
        throw std::logic_error("Invalid number of arguments");
      }
      roeRule.bindParameter(param, *argIt);
      ++argIt;
    }
  }

  std::string Module::errorText() const
  {
    return driver_->errorText();
  }

  bool Module::constructAST(const std::string& text)
  {
    return driver_->parse_string(text);
  }

  bool Module::constructAST(const std::istream& in)
  {
    return driver_->parse_stream(in);
  }

  void Module::compileToIR()
  {
    if (compiled_)
    {
        throw std::logic_error("Module is already compiled");
    }

    try
    {
      driver_->rules().evaluate();

      compiled_ = true;
    }
    catch(ASTException& ex)
    {
      std::ostringstream ostrm;
      ostrm << "Failed to generate IR code from AST due to:" << ex.what();
      throw std::runtime_error(ostrm.str());
    }
  }

  void Module::dumpIR(std::ostream& ostrm)
  {
    if (!compiled_)
    {
      std::logic_error("Module is not compiled to IR yet");
    }

    /*std::string       out;
    module_->print(out, nullptr);
    ostrm << out << std::endl;*/
  }

  void Module::buildNative()
  {
    if (!compiled_)
    {
      std::logic_error("Module is not compiled to IR yet");
    }

    context_.externalFunctions().addAllMappings(*executionEngine_);

    llvm::PassManagerBuilder builder;
    llvm::legacy::FunctionPassManager passManager(module_);
    // -O3,  no size opt, aggressive inlining
    builder.OptLevel = 3;
    builder.SizeLevel = 0;
    builder.Inliner = llvm::createFunctionInliningPass();
    builder.populateFunctionPassManager(passManager);
    passManager.doInitialization();
    for (const auto& rule : context_.rules())
    {
      auto* fptr = rule.second->funcPtr();
      if (fptr)
      {
        passManager.run(*fptr);
      }
    }

    for (const auto& rule : context_.rules())
    {
      size_t               nParams = rule.second->params().size();
      CompiledFunctionInfo info(rule.first, nParams, executionEngine_);
      compiledFunctions_[rule.first] = info;
    }
  }
}
