#include <AST/ASTAssignment.h>
#include <AST/ASTCStr.h>
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
    if (isCStr(from))
    {
      auto astCStr = std::dynamic_pointer_cast<ASTCstr>(right_);
      context_.externalFunctions().makeCall(StringOps::ASSIGN_CHPTR, {to, from, astCStr->length()});
    }
    else if (isString(from))
    {
      context_.externalFunctions().makeCall(StringOps::ASSIGN_STR, {to, from});
    }
    else
    {
      throw ASTException() << "Failed to produce assignment";
    }
  }

  void ASTAssignment::processAssignmentToLocalFloatVar(const ASTVariable& var, llvm::Value* to, llvm::Value* from)
  {
    context_.builder().CreateStore(from, to);
  }

  void ASTAssignment::processAssignmentToField(const ASTVariable& astVar, llvm::Value* from)
  {
    llvm::Value* container   = context_.rule().getParamValue(astVar.baseName());
    llvm::Value* tagVal      = llvm::ConstantInt::get(context_.types().longType(), astVar.tag());
    auto         constraints = context_.rule().getContainerForParam(astVar.baseName());

    if (isCStr(from))
    {
      if (constraints && !constraints->stringAssignmentAllowed(astVar.tag()))
      {
        throw ASTException() << "String assignment is not allowed";
      }

      auto astCStr = std::dynamic_pointer_cast<ASTCstr>(right_);
      context_.externalFunctions().makeCall(Bindings::SET_FIELD_CHPTR, {container, tagVal, from, astCStr->length()});
    }
    else if (isString(from))
    {
      if (constraints && !constraints->stringAssignmentAllowed(astVar.tag()))
      {
        throw ASTException() << "String assignment is not allowed";
      }
      context_.externalFunctions().makeCall(Bindings::SET_FIELD_STRING, {container, tagVal, from});
    }
    else if (isLong(from))
    {
      if (!constraints || !constraints->longAssignmentAllowed(astVar.tag()))
      {
        throw ASTException() << "Long assignment is not allowed";
      }

      context_.externalFunctions().makeCall(Bindings::SET_FIELD_INT, {container, tagVal, from});
    }
    else if (isFloat(from))
    {
      if (!constraints || !constraints->doubleAssignmentAllowed(astVar.tag()))
      {
        throw ASTException() << "Long assignment is not allowed";
      }

      context_.externalFunctions().makeCall(Bindings::SET_FIELD_DOUBLE, {container, tagVal, from});
    }
    else
    {
      throw ASTException() << "Failed to produce assignment(field)";
    }
  }

  void ASTAssignment::processAssignmentToLocalIntVar(const ASTVariable& var, llvm::Value* to, llvm::Value* from)
  {
    context_.builder().CreateStore(from, to);
  }

  llvm::Value* ASTAssignment::evaluate()
  {
    auto from   = right_->evaluate();
    from        = loadValueIfNeeded(from);
    auto astVar = std::dynamic_pointer_cast<ASTVariable>(left_);

    if (!isCStr(from) && !isString(from) && !isLong(from) && !isFloat(from))
    {
        throw ASTException() << "Invalid assignment rvalue type";
    }

    if (!astVar)
    {
      throw ASTException() << "Expected variable";
    }

    if (astVar->isField())
    {
      astVar->processContainerField();
      processAssignmentToField(*astVar, from);
    }
    else
    {
      llvm::Type* varType = context_.types().varTypeFromRVal(from->getType());
      context_.rule().getOrCreateVariable(astVar->name(), varType);

      auto* to = left_->evaluate();

      if (isString(to))
      {
        processAssignmentToLocalStrVar(*astVar, to, from);
      }
      else if (isLongPtr(to))
      {
        processAssignmentToLocalIntVar(*astVar, to, from);
      }
      else if (isFloatPtr(to))
      {
        processAssignmentToLocalFloatVar(*astVar, to, from);
      }
      else
      {
        throw ASTException() << "Invalid assignment";
      }
    }

    return nullptr;
  }
}
