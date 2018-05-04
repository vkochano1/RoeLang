#pragma once 

#include <Context.h>
#include <llvm/IR/DerivedTypes.h>
#include <AST/ASTException.h>

namespace roe
{
    class ASTElement
    {
    public:
        using ASTElementPtr = std::shared_ptr<ASTElement>;
        using ASTElementCollection = std::vector<ASTElementPtr>;    
    public:
        ASTElement(Context& context);
        
    public:
        virtual  llvm::Value* evaluate () = 0;
        virtual ~ASTElement() {};
    protected:
        llvm::Value* loadValueIfNeeded(llvm::Value* value);
    protected:
        Context& context_;
    };

}



