#include <AST/ASTElement.h>

namespace roe
{


  void ASTElement::normalizeValues(llvm::Value*& v1, llvm::Value*& v2)
  {
      auto& builder = context_.builder();

      bool isV1Float =  v1->getType() == context_.types().floatType();
      bool isV2Float =  v2->getType() == context_.types().floatType();

      bool isV1String = v1->getType() == context_.types().stringPtrType();
      bool isV2String = v2->getType() == context_.types().stringPtrType();

      bool isV1CharPtr = v1->getType() == context_.types().charPtrType();
      bool isV2CharPtr = v2->getType() == context_.types().charPtrType();

      bool isV1Long =  v1->getType() == context_.types().longType();
      bool isV2Long =  v2->getType() == context_.types().longType();

      bool isV1Number = isV1Long || isV1Float;
      bool isV2Number = isV2Long || isV2Float;

      if( isV1Float && isV2Long)
      {
          v2 = builder.CreateSIToFP(v2, context_.types().floatType());
      }
      else if (isV1Long && isV2Float)
      {
          v1 = builder.CreateSIToFP(v1, context_.types().floatType());
      }
      else if (isV1Number ^ isV2Number)
      {
          throw ASTException("Can't normalize values");
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
