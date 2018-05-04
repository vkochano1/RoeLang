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

    void ASTAssignment::processAssignmentToLocalStrVar(const ASTVariable& var, llvm::Value* to, llvm::Value* from)
    {
        if(from->getType() == Types::instance().charPtrType())
        {
            FunctionRegistrar::instance().makeCall(context_,StringOps::ASSIGN_CHPTR, {to, from} );
        }
        else
        {
            FunctionRegistrar::instance().makeCall(context_,StringOps::ASSIGN_STR, {to, from} );
        }
    }
        
    void ASTAssignment::processAssignmentToField(const ASTVariable& astVar, llvm::Value* to, llvm::Value* from)
    {
        llvm::Value* container = context_.rule().getParamValue(astVar.baseName());
        llvm::Value* tagVal = llvm::ConstantInt::get(Types::instance().longType(), astVar.tag());  
        
        if(from->getType() == Types::instance().charPtrType())
        {
            FunctionRegistrar::instance().makeCall(context_,"setFieldCharPtr", {container, tagVal, from} );
        }
        else
        {
            FunctionRegistrar::instance().makeCall(context_,"setField", {container, tagVal, from} );
        }
    }
    
    void ASTAssignment::processAssignmentToLocalIntVar(const ASTVariable& var, llvm::Value* to, llvm::Value* from)
    {
        from = loadValueIfNeeded(from);
        context_.builder().CreateStore(from, to); 
    }
    
    llvm::Value* ASTAssignment::evaluate()
    {
        auto from = right_->evaluate();
        auto* astVar = dynamic_cast<ASTVariable*>(left_.get());
        
        {
            llvm::Type* varType = Types::instance().varTypeFromRVal(from->getType());
            context_.getOrCreateVariable(astVar->name(), varType); 
        }
        
        auto* to = left_->evaluate();
        
        if(astVar->isField())
        {
            processAssignmentToField(*astVar, to, from);
        }
        else if(to->getType() == Types::instance().stringPtrType() )
        {
            processAssignmentToLocalStrVar(*astVar, to, from);
        }
        else 
        {
            processAssignmentToLocalIntVar(*astVar, to, from);            
        }
            
        return to;
    }
 
}
