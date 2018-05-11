#include <Module/Module.h>
#include <Functions/Bindings.h>


namespace roe
{
    Module::Module(const std::string& name)
    {
        {
            auto module = std::make_unique<llvm::Module>(name, context_);
            module_ = module.get();
            engineBuilder_ = std::make_unique<llvm::EngineBuilder> (std::move(module));
            executionEngine_ = engineBuilder_->create();
        }

        context_.init(module_);

        roe::StringOps::registerBuiltins(context_);
        roe::Bindings::registerBuiltins(context_);

        driver_ = std::make_unique<roe::Driver> (context_);

    }

    void  Module::bindFunctionParameterConstrains(const std::string& functionName
                                        ,std::initializer_list<std::shared_ptr<IContainerAccess> > accessList)
    {
      auto& roeRule = context().rule(functionName);
      auto argIt = accessList.begin();

      for (const auto& param : roeRule.params())
      {
        if (argIt == accessList.end())
        {
          throw std::logic_error("Invalid number of arguments");
        }
        roeRule.bindParameter(param, *argIt);
        ++argIt;
      }
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
        driver_->rules().evaluate();
    }

    void Module::dumpIR()
    {
        using namespace llvm;
        std::string std_file_stream;
        raw_string_ostream file_stream(std_file_stream);
        module_->print(file_stream, nullptr);
        std::cout << std_file_stream << std::endl;
    }

    void Module::buildNative()
    {
        context_.externalFunctions().addAllMappings(*executionEngine_);

        for( const auto& rule : context_.rules())
        {
                size_t nParams = rule.second->params().size();
                CompiledFunctionInfo info(rule.first, nParams, executionEngine_);
                compiledFunctions_[rule.first] = info;
        }

    }


}
