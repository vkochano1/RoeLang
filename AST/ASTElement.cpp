#include <AST/ASTElement.h>

namespace roe
{
    llvm::Value* ASTElement::loadValueIfNeeded(llvm::Value* value)
    {
        if (value->getType()->isPointerTy() 
            && value->getType() != context_.types().stringPtrType()
            && value->getType() != context_.types().charPtrType()
           )
        {
            return  context_.builder().CreateLoad(value);
        }
        return value;
    }
    
    ASTElement::ASTElement(Context& context)
     : context_(context)
    {
    }    
}

