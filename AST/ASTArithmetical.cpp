#include <AST/ASTArithmetical.h>
#include <FunctionRegistrar.h>

namespace roe
{
   ASTArithmetical::ASTArithmetical(Context& context, Operator op, ASTElementPtr op1, ASTElementPtr op2)
    :ASTElement(context)
    , op_(op)
    , operand1_(op1)
    , operand2_(op2)
    {
        
    }
    llvm::Value* ASTArithmetical::evaluate()
    {
      auto& builder = context_.builder();
      
      auto v1 = operand1_->evaluate();
      auto v2 = operand2_->evaluate();
      
      v1 = loadValueIfNeeded(v1);
      v2 = loadValueIfNeeded(v2);
      
      llvm::Value* out = nullptr;
      switch(op_)
      {
          case Operator::PLUS :
          {
              std::cerr << "PLUS";
              llvm::errs() << *v2;
              std::cerr << std::endl;
              if( v1->getType() == Types::instance().stringPtrType())
              {
                  out = builder.CreateAlloca(Types::instance().stringType());
            
                  if(v2->getType() != Types::instance().stringPtrType())
                  {
                      FunctionRegistrar::instance().makeCall(context_,"concatSCHPtr", { v1, v2, out} );
              
                  }
                  else
                  {
                      FunctionRegistrar::instance().makeCall(context_,"concat", { v1, v2, out} );
                  }
            }
              else
              {
                out = builder.CreateAdd(v1,v2);
              }
          }
          break;
           case Operator::MINUS :
              out = builder.CreateSub(v1,v2);
          break;
           case Operator::MUL :
              out = builder.CreateMul(v1,v2);
          break;
           case Operator::DIV :
              out = builder.CreateExactSDiv(v1,v2);
          break;
      };
      
      return out;   
    }
    
}
