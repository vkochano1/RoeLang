#include <AST/ASTAssignment.h>
#include <AST/ASTVariable.h>

#include <FunctionRegistrar.h>

namespace roe
{
  
    ASTAssignment::ASTAssignment(Context& context, ASTElementPtr left, ASTElementPtr right)
    : ASTElement(context)
    , left_(left)
    , right_(right)
    {
       
    }

        
    llvm::Value* ASTAssignment::evaluate()
    {
        auto rightVal = right_->evaluate();
        auto* astVar = dynamic_cast<ASTVariable*>(left_.get());
        
        llvm::Type* varType = Types::instance().varTypeFromRVal(rightVal->getType());
        auto v1 = context_.getOrCreateVariable(astVar->name(), varType); 
        
        auto* leftVal = left_->evaluate();
        
        if(astVar->isField())
        {
             llvm::Value* container = context_.rule().getParamValue(astVar->baseName());
             llvm::Value* tagVal = llvm::ConstantInt::get(Types::instance().longType(), astVar->tag());              
               if(rightVal->getType() == Types::instance().charPtrType())
               {
                  FunctionRegistrar::instance().makeCall(context_,"setFieldCharPtr", {container, tagVal, rightVal} );
               }
               else
               {
                 FunctionRegistrar::instance().makeCall(context_,"setField", {container, tagVal, rightVal} );
               }
             
        }
        if(leftVal->getType() == Types::instance().stringPtrType() )
        {
               
               if(rightVal->getType() == Types::instance().charPtrType())
               {
                        FunctionRegistrar::instance().makeCall(context_,"inits", {leftVal, rightVal} );
               }
               else
               {
                        FunctionRegistrar::instance().makeCall(context_,"assign", {leftVal, rightVal} );
               }
        }
        else 
        {
                rightVal = loadValueIfNeeded(rightVal);
                context_.builder().CreateStore(rightVal, leftVal); 
                           
        }
            
        return leftVal;
    }
 
}
