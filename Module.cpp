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
    
        roe::Types::instance().init(context_);
    
        roe::StringOps::registerBuilins(context_);

        roe::Bindings::registerBuiltins(context_);

    }
    
    void Module::compileToIR(const std::string& text)
    {
        roe::Driver driver (context_);
        
        if(driver.parse_string(text))
        {        
            driver.rules().evaluate();
        }        
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

