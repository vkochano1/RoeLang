#include <Exceptions/ASTException.h>
#include <Functions/FunctionRegistrar.h>
#include <Module/Context.h>
#include <assert.h>
#include <iostream>

namespace roe
{
  class DefaultPrinter : public IPrinter
  {
  public:
    void print(const StringOps::String_t* str)
    {
      std::cout << std::string(str->c_str(), str->length()) << std::endl;
    }

    void print(int64_t iVal)
    {
      std::cout << iVal << std::endl;
    }

    void print(double dVal)
    {
      std::cout << dVal << std::endl;
    }

    void print(const char* cstr)
    {
      std::cout << cstr << std::endl;
    }
  };
  ////////////////////////
  Context::Context()
  {
    module_ = nullptr;
    printer_.reset(new DefaultPrinter());
    types_             = std::make_unique<Types>(*this);
    functionRegistrar_ = std::make_unique<FunctionRegistrar>(*this);
  }

  IPrinter* Context::printer()
  {
    return printer_.get();
  }

  FunctionRegistrar& Context::externalFunctions()
  {
    return *functionRegistrar_;
  }

  void Context::addNewRule(const std::string& newRuleName, const ASTFunctionParameters::Parameters& params)
  {
    auto rule = std::make_shared<RoeRule>(*this, newRuleName, params);
    auto rit  = rules_.insert(std::make_pair(newRuleName, rule));
    if (rit.second == false)
    {
      throw ASTException() << "Duplicate rule";
    }
  }

  void Context::init(Module* module)
  {
    module_ = module;
  }

  RoeRule& Context::rule(const std::string& name)
  {
    return *rules_[name];
  }

  Context::~Context()
  {
  }

  Types& Context::types()
  {
    return *types_;
  }

  void Context::setCurrentRule(const std::string& name)
  {
    auto fit = rules_.find(name);
    if (fit == rules_.end())
    {
      throw ASTException() << "Unknonw rule";
    }
    currentRule_ = fit->second;
  }

  Module* Context::module()
  {
    return module_;
  }

  RoeRule& Context::rule()
  {
    return *currentRule_;
  }

  Context::Rules& Context::rules()
  {
    return rules_;
  }

  RoeRule::Builder& Context::builder()
  {
    return rule().builder();
  };
}
