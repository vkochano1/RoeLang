#include <AST/ASTElement.h>

namespace roe
{

  void ASTElement::normalizeValues(llvm::Value*& v1, llvm::Value*& v2)
  {
      auto& builder = context_.builder();

      if(v1->getType() == context_.types().floatType()
          && v2->getType() != context_.types().floatType())
      {
          v2 = builder.CreateSIToFP(v2, context_.types().floatType());
      }
  }

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
