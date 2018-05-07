#include <Module.h>
#include <Bindings.h>


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

    bool Module::constructAST(const std::string& text)
    {
        return driver_->parse_string(text);
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
        roe::FunctionRegistrar::instance().addAllMappings(*executionEngine_);

        for( const auto& rule : context_.rules())
        {
                CompiledFunctionInfo info(rule.first, executionEngine_);
                compiledFunctions_[rule.first] = info;
        }

    }


}
