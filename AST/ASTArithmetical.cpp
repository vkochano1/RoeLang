#include <AST/ASTArithmetical.h>
#include <FunctionRegistrar.h>
#include <StringOps.h>

namespace roe
{
   ASTArithmetical::ASTArithmetical(Context& context, Operator op, ASTElementPtr op1, ASTElementPtr op2)
    :ASTElement(context)
    , op_(op)
    , operand1_(op1)
    , operand2_(op2)
    {        
    }
    
    bool ASTArithmetical::processStringConcat(llvm::Value* left
                                            , llvm::Value* right
                                            , llvm::Value*& out)
    {
        auto& builder = context_.builder();
      
        out = nullptr;
        
        if(    left->getType() == Types::instance().stringPtrType() 
            && right->getType() == Types::instance().stringPtrType())
        {
            out = builder.CreateAlloca(Types::instance().stringType());
            FunctionRegistrar::instance().makeCall(context_,StringOps::CONCAT_STR_AND_STR, { left, left, right} );
        }
        else if (left->getType() == Types::instance().stringPtrType() 
                 && right->getType() == Types::instance().charPtrType()
                )
        {
            out = builder.CreateAlloca(Types::instance().stringType());
            FunctionRegistrar::instance().makeCall(context_,StringOps::CONCAT_STR_AND_CHPTR, { left, right, out} );
        }
        else if (left->getType() == Types::instance().charPtrType() 
                 && right->getType() == Types::instance().stringPtrType()
                )
        {
            out = builder.CreateAlloca(Types::instance().stringType());
            FunctionRegistrar::instance().makeCall(context_,StringOps::CONCAT_CHPTR_AND_STR, { left, right, out} );
        }
        else if (left->getType() == Types::instance().charPtrType() 
                 && right->getType() == Types::instance().charPtrType()
                )
        {
            out = builder.CreateAlloca(Types::instance().stringType());
            FunctionRegistrar::instance().makeCall(context_,StringOps::CONCAT_CHPTR_AND_CHPTR, { left, right, out} );
        }
        
        return out != nullptr;
    }
    
    llvm::Value* ASTArithmetical::evaluate()
    {
      auto& builder = context_.builder();
      
      auto left = operand1_->evaluate();
      auto right = operand2_->evaluate();
      
      left = loadValueIfNeeded(left);
      right = loadValueIfNeeded(right);
      
      llvm::Value* out = nullptr;
      switch(op_)
      {
          case Operator::PLUS :
          {
            bool processed = processStringConcat(left, right, out);
            if (processed)
            {
                return out;
            }
                
            out = builder.CreateAdd(left,right);
          }
          break;
          
           case Operator::MINUS :
              out = builder.CreateSub(left,right);
          break;
          
           case Operator::MUL :
              out = builder.CreateMul(left,right);
          break;
          
           case Operator::DIV :
              out = builder.CreateExactSDiv(left,right);
          break;
      };
      
      return out;   
    }
    
}
