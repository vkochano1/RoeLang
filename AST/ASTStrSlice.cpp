#include <AST/ASTStrSlice.h>
#include <FunctionRegistrar.h>

namespace roe
{
 
    ASTStrSlice::ASTStrSlice(Context& context
    , ASTElement::ASTElementPtr base
    , ASTElement::ASTElementPtr from
    , ASTElement::ASTElementPtr len)
        : ASTElement(context)
        , base_(base)
        , len_(len)
        , from_(from)
     {
            
     }
     
     llvm::Value* ASTStrSlice::evaluate()
     {
         auto* varValue = base_->evaluate();
         auto* idx = from_->evaluate();
         
         llvm::Value* out = nullptr;
         if( !len_ )
         {
          out =FunctionRegistrar::instance().makeCall(context_,StringOps::GET_CHAR, { varValue, idx} );
         }
         else
         {
           auto* l = len_->evaluate();
          out = context_.rule().builder().CreateAlloca(context_.types().stringType());
           FunctionRegistrar::instance().makeCall(context_,StringOps::GET_SUBSTR, { varValue, idx, l, out} );
         }
            
         return out;
     }
}
