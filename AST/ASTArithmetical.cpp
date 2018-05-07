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
    
    void ASTArithmetical::normalizeValues(llvm::Value*& v1, llvm::Value*& v2)
    {
        auto& builder = context_.builder();
        
        
        if(v1->getType() == context_.types().floatType()
            && v2->getType() != context_.types().floatType())
        {
            std::cerr << "STEP1" << std::endl;
            v2 = builder.CreateSIToFP(v2, context_.types().floatType());
        }
        std::cerr << "STEP2" << std::endl;
        llvm::errs() << *v1->getType() <<"  "<<*v2->getType();
    }
    
    bool ASTArithmetical::processStringConcat(llvm::Value* left
                                            , llvm::Value* right
                                            , llvm::Value*& out)
    {
        auto& builder = context_.builder();
      
        out = nullptr;
        
        if(    left->getType() == context_.types().stringPtrType() 
            && right->getType() == context_.types().stringPtrType())
        {
            out = builder.CreateAlloca(context_.types().stringType());
            FunctionRegistrar::instance().makeCall(context_,StringOps::CONCAT_STR_AND_STR, { left, left, right} );
        }
        else if (left->getType() == context_.types().stringPtrType() 
                 && right->getType() == context_.types().charPtrType()
                )
        {
            out = builder.CreateAlloca(context_.types().stringType());
            FunctionRegistrar::instance().makeCall(context_,StringOps::CONCAT_STR_AND_CHPTR, { left, right, out} );
        }
        else if (left->getType() == context_.types().charPtrType() 
                 && right->getType() == context_.types().stringPtrType()
                )
        {
            out = builder.CreateAlloca(context_.types().stringType());
            FunctionRegistrar::instance().makeCall(context_,StringOps::CONCAT_CHPTR_AND_STR, { left, right, out} );
        }
        else if (left->getType() == context_.types().charPtrType() 
                 && right->getType() == context_.types().charPtrType()
                )
        {
            out = builder.CreateAlloca(context_.types().stringType());
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
      
      normalizeValues(left,right);
      
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
            
            if(left->getType() == context_.types().floatType())
                out = builder.CreateFAdd(left,right);
            else
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
