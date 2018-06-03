#pragma once

#include <Functions/Bindings.h>
#include <Module/RoeRule.h>
#include <Types/Types.h>
#include <regex>

namespace roe
{
  class FunctionRegistrar;
  class Context;
  class Module;

  class Context final
  {
  public:
    using Rules = std::unordered_map<std::string, std::shared_ptr<RoeRule>>;
    using RegexPtr = std::unique_ptr<std::regex>;
    using RegexPtrContainer = std::vector<RegexPtr>;

  public:
    Context();
    ~Context();

    Context(const Context&) = delete;
    Context& operator=(const Context&) = delete;

    void init(Module* module);

  public:
    Module*  module();
    RoeRule& rule();
    Rules&   rules();
    RoeRule& rule(const std::string& name);
    Types&             types();
    IPrinter*          printer();
    RoeRule::Builder&  builder();
    llvm::LLVMContext& native();

  public:
    void addNewRule(const std::string& newRuleName, const RoeRule::FunctionParameters& params);
    void* addMatchRegex(const std::string& regex);
    void setCurrentRule(const std::string& name);
    FunctionRegistrar& externalFunctions();

  private:
    Rules                              rules_;
    Module*                            module_;
    std::shared_ptr<RoeRule>           currentRule_;
    std::unique_ptr<Types>             types_;
    std::unique_ptr<llvm::LLVMContext> nativeContext_;
    std::unique_ptr<IPrinter>          printer_;
    std::unique_ptr<FunctionRegistrar> functionRegistrar_;
    RegexPtrContainer                  regexPtrContainer_;
  };
}
