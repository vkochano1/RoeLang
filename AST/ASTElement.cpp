#include <AST/ASTElement.h>

namespace roe
{
    llvm::Value* ASTElement::loadValueIfNeeded(llvm::Value* value)
    {
        if (value->getType()->isPointerTy() 
            && value->getType() != Types::instance().stringPtrType()
            && value->getType() != Types::instance().charPtrType()
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

