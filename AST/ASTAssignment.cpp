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
        else if (from->getType() == context_.types().stringPtrType())
        {
            context_.externalFunctions().makeCall(StringOps::ASSIGN_STR, {to, from} );
        }
        else
        {
          throw ASTException("Failed to produce assignment");
        }
    }


    void ASTAssignment::processAssignmentToLocalFloatVar(const ASTVariable& var, llvm::Value* to, llvm::Value* from)
    {
        context_.builder().CreateStore(from, to);
    }

    void ASTAssignment::processAssignmentToField(const ASTVariable& astVar, llvm::Value* from)
    {

        llvm::Value* container = context_.rule().getParamValue(astVar.baseName());
        llvm::Value* tagVal = llvm::ConstantInt::get(context_.types().longType(), astVar.tag());

        if(from->getType() == context_.types().charPtrType())
        {
            context_.externalFunctions().makeCall(Bindings::SET_FIELD_CHPTR, {container, tagVal, from} );
        }
        else if (from->getType() == context_.types().stringPtrType())
        {
            context_.externalFunctions().makeCall(Bindings::SET_FIELD_STRING, {container, tagVal, from} );
        }
        else if (from->getType() == context_.types().longType())
        {
            context_.externalFunctions().makeCall(Bindings::SET_FIELD_INT, {container, tagVal, from} );
        }
        else if (from->getType() == context_.types().floatType())
        {
            context_.externalFunctions().makeCall(Bindings::SET_FIELD_DOUBLE, {container, tagVal, from} );
        }
        else
        {
          throw ASTException("Failed to produce assignment(field)");
        }
    }

    void ASTAssignment::processAssignmentToLocalIntVar(const ASTVariable& var, llvm::Value* to, llvm::Value* from)
    {
        context_.builder().CreateStore(from, to);
    }

    llvm::Value* ASTAssignment::evaluate()
    {
        auto from = right_->evaluate();
        from = loadValueIfNeeded(from);
        auto* astVar = dynamic_cast<ASTVariable*>(left_.get());

        if(astVar->isField())
        {
            astVar->processContainerField();
            processAssignmentToField(*astVar, from);
        }
        else
        {
          llvm::Type* varType = context_.types().varTypeFromRVal(from->getType());
          context_.rule().getOrCreateVariable(astVar->name(), varType);
          auto* to = left_->evaluate();
          if(to->getType() == context_.types().stringPtrType() )
          {
              processAssignmentToLocalStrVar(*astVar, to, from);
          }
          else if(to->getType() == context_.types().longPtrType())
          {
              processAssignmentToLocalIntVar(*astVar, to, from);
          }
          else if(to->getType() == context_.types().floatPtrType())
          {
            processAssignmentToLocalFloatVar(*astVar, to, from);
          }
          else
          {
            throw ASTException("Invalid assignment");
          }
        }

        return nullptr;
    }

}
