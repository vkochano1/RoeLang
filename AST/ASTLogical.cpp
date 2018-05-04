#include <AST/ASTLogical.h>
#include <FunctionRegistrar.h>

namespace roe
{

    ASTLogical::ASTLogical(Context& context, Operator op, ASTElementPtr op1, ASTElementPtr op2)
    :ASTElement(context)
    , op_(op)
    , operand1_(op1)
    , operand2_(op2)
    {
        
    }
    llvm::Value* ASTLogical::evaluate()
    {
      auto& builder = context_.builder();
      
      auto v1 = operand1_->evaluate();
      auto v2 = operand2_->evaluate();
      
      v1 = loadValueIfNeeded(v1);
      v2 = loadValueIfNeeded(v2);
      
      llvm::Value* out = nullptr;
      switch(op_)
      {
          case Operator::AND :
              out = builder.CreateAnd(v1, v2);
          break;
           case Operator::OR :
              out = builder.CreateOr(v1, v2);
          break;
      };
      
      return out;      
    }
  
    ASTLogicalNOT::ASTLogicalNOT(Context& context, ASTElementPtr op1)
    : ASTElement(context)
    , operand1_(op1)
    {
        
    }
    llvm::Value* ASTLogicalNOT::evaluate()
    {
      auto& builder = context_.builder();
      auto* value = operand1_->evaluate();
      value = loadValueIfNeeded(value);
      return  builder.CreateNot(value);   
    }
    
    
    ASTCompare::ASTCompare(Context& context, Operator op, ASTElementPtr op1, ASTElementPtr op2)
    :ASTElement(context)
    , op_(op)
    , operand1_(op1)
    , operand2_(op2)
    {
        
    }
    llvm::Value* ASTCompare::evaluate()
    {
      auto& builder = context_.builder();
      
      auto v1 = operand1_->evaluate();
      auto v2 = operand2_->evaluate();
      
      v1 = loadValueIfNeeded(v1);
      v2 = loadValueIfNeeded(v2);
      
      llvm::Value* out = nullptr;
      switch(op_)
      {
          case Operator::LESS :
              out = builder.CreateICmpSLT(v1,v2);
          break;
           case Operator::MORE :
              out = builder.CreateICmpSGT(v1,v2);
          break;
           case Operator::EQUAL :
           {
              if( v1->getType() == Types::instance().stringPtrType()
                  && v2->getType() == Types::instance().stringPtrType()
                )
              {
                  out = FunctionRegistrar::instance().makeCall(context_,StringOps::EQUALS_STR_AND_STR, { v1, v2 } );
              }
              else  if( v1->getType() == Types::instance().charPtrType()
                      && v2->getType() == Types::instance().stringPtrType()
                      )
              {
                    out = FunctionRegistrar::instance().makeCall(context_,StringOps::EQUALS_CHPTR_AND_STR, { v1, v2 } );
              }
              else  if( v1->getType() == Types::instance().stringPtrType()
                      && v2->getType() == Types::instance().charPtrType()
                      )
              {
                    out = FunctionRegistrar::instance().makeCall(context_,StringOps::EQUALS_STR_AND_CHPTR, { v1, v2 } );
              }
              else  if( v1->getType() == Types::instance().charPtrType()
                      && v2->getType() == Types::instance().charPtrType()
                      )
              {
                    out = FunctionRegistrar::instance().makeCall(context_,StringOps::EQUALS_CHPTR_AND_CHPTR, { v1, v2 } );
              }
              
              else
              {
                  out = builder.CreateICmpEQ(v1,v2);
              }
           }
          break;
           case Operator::NOT_EQUAL :
              out = builder.CreateICmpNE(v1,v2);
          break;
           case Operator::MORE_OR_EQUAL :
              out = builder.CreateICmpSGE(v1,v2);
          break;
           case Operator::LESS_OR_EQUAL :
              out = builder.CreateICmpSLE(v1,v2);
          break;
          
      };
      
      return out; 
        
    }

}
