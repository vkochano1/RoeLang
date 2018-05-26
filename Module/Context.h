#pragma once

#include <assert.h>

#include <Types/Types.h>
#include <iostream>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/IR/Module.h>
#include <tuple>

#include <Functions/Bindings.h>
#include <Module/RoeRule.h>

namespace roe
{
  class FunctionRegistrar;
  class Context;
  class Module;

  class Context final : public llvm::LLVMContext
  {
  public:
    using Rules = std::unordered_map<std::string, std::shared_ptr<RoeRule>>;

  public:
    Context();
    Context(const Context&) = delete;
    Context& operator=(const Context&) = delete;
    ~Context();

    void init(Module* module);

  public:
    Module*  module();
    RoeRule& rule();
    Rules&   rules();
    RoeRule& rule(const std::string& name);
    Types&            types();
    IPrinter*         printer();
    RoeRule::Builder& builder();

  public:
    void addNewRule(const std::string& newRuleName, const ASTFunctionParameters::Parameters& params);
    void setCurrentRule(const std::string& name);
    FunctionRegistrar& externalFunctions();

  private:
    Rules                              rules_;
    Module*                            module_;
    std::shared_ptr<RoeRule>           currentRule_;
    std::unique_ptr<Types>             types_;
    std::unique_ptr<IPrinter>          printer_;
    std::unique_ptr<FunctionRegistrar> functionRegistrar_;
  };
}
