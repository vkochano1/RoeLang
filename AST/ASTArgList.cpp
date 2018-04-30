#include <AST/ASTArgList.h>

namespace roe
{
    ASTArgList::ASTArgList(Context& context)
      : ASTElement(context)
    {
        
    }
    
    void ASTArgList::addArgument(ASTElementPtr arg)
    {
        args_.push_back(arg);
    }
    
    size_t ASTArgList::size() const
    {
        return args_.size();
    }
    
    llvm::Value* ASTArgList::evaluate()
    {
            for (auto& arg : args_)
            {
                auto* val = arg->evaluate();
                
                val = loadValueIfNeeded(val);
               
                values_.push_back(val);
            }
            
            return nullptr;   
    }
    
    const ASTArgList::EvaluatedValues& ASTArgList::values() const
    {
        return values_;
    }

}
