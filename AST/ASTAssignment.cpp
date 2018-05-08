#include <AST/ASTAssignment.h>
#include <AST/ASTVariable.h>

#include <Functions/FunctionRegistrar.h>

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
        if(from->getType() == context_.types().charPtrType())
        {
            context_.externalFunctions().makeCall(StringOps::ASSIGN_CHPTR, {to, from} );
        }
        else
        {
            context_.externalFunctions().makeCall(StringOps::ASSIGN_STR, {to, from} );
        }
    }


    void ASTAssignment::processAssignmentToLocalFloatVar(const ASTVariable& var, llvm::Value* to, llvm::Value* from)
    {
        from = loadValueIfNeeded(from);
        context_.builder().CreateStore(from, to);
    }

    void ASTAssignment::processAssignmentToField(const ASTVariable& astVar, llvm::Value* to, llvm::Value* from)
    {
        llvm::Value* container = context_.rule().getParamValue(astVar.baseName());
        llvm::Value* tagVal = llvm::ConstantInt::get(context_.types().longType(), astVar.tag());

        if(from->getType() == context_.types().charPtrType())
        {
            context_.externalFunctions().makeCall(Bindings::SET_FIELD_CHPTR, {container, tagVal, from} );
        }
        else
        {
            context_.externalFunctions().makeCall(Bindings::SET_FIELD_STRING, {container, tagVal, from} );
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
            llvm::Type* varType = context_.types().varTypeFromRVal(from->getType());
            context_.rule().getOrCreateVariable(astVar->name(), varType);
        }

        auto* to = left_->evaluate();

        if(astVar->isField())
        {
            processAssignmentToField(*astVar, to, from);
        }
        else if(to->getType() == context_.types().stringPtrType() )
        {
            processAssignmentToLocalStrVar(*astVar, to, from);
        }
        else if(to->getType() == context_.types().longPtrType())
        {
            processAssignmentToLocalIntVar(*astVar, to, from);
        }
        else
        {
            processAssignmentToLocalFloatVar(*astVar, to, from);
        }

        return to;
    }

}
