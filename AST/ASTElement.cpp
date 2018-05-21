#include <AST/ASTElement.h>

namespace roe
{

  llvm::Value* ASTElement::allocBool()
  {
    return context_.builder().CreateAlloca(context_.types().boolType());
  }

  llvm::Value* ASTElement::allocFloat()
  {
    return context_.builder().CreateAlloca(context_.types().floatType());
  }

  llvm::Value* ASTElement::allocLong()
  {
    return context_.builder().CreateAlloca(context_.types().longType());
  }

  llvm::Value* ASTElement::allocString()
  {
    return context_.builder().CreateAlloca(context_.types().stringType());
  }

  bool ASTElement::isBool(const llvm::Value* value)
  {
    return value->getType() == context_.types().boolType();
  }

  bool ASTElement::isFloat(const llvm::Value* value)
  {
    return value->getType() == context_.types().floatType();
  }

  bool ASTElement::isLong(const llvm::Value* value)
  {
    return value->getType() == context_.types().longType();
  }

  bool ASTElement::isFloatPtr(const llvm::Value* value)
  {
    return value->getType() == context_.types().floatPtrType();
  }

  bool ASTElement::isLongPtr(const llvm::Value* value)
  {
    return value->getType() == context_.types().longPtrType();
  }

  bool ASTElement::isString(const llvm::Value* value)
  {
    return value->getType() == context_.types().stringPtrType();
  }

  bool ASTElement::isCStr(const llvm::Value* value)
  {
    return value->getType() == context_.types().charPtrType();
  }

  void ASTElement::normalizeValues(llvm::Value*& v1, llvm::Value*& v2)
  {
    auto& builder = context_.builder();

    bool isV1Number = isLong(v1) || isFloat(v1);
    bool isV2Number = isLong(v2) || isFloat(v2);

    if (isFloat(v1) && isLong(v2))
    {
      v2 = builder.CreateSIToFP(v2, context_.types().floatType());
    }
    else if (isFloat(v2) && isLong(v1))
    {
      v1 = builder.CreateSIToFP(v1, context_.types().floatType());
    }
    else if (isV1Number ^ isV2Number)
    {
      throw ASTException() << "Can't normalize values";
    }
  }

  llvm::Value* ASTElement::convertToBool(llvm::Value* v)
  {
    auto& builder = context_.builder();
    if (isFloat(v))
    {
      return builder.CreateFPToSI(v, context_.types().boolType());
    }
    else if (isLong(v))
    {
      auto* zero = llvm::ConstantInt::get(context_.types().longType(), 0);
      return builder.CreateICmpNE(v, zero);
    }

    return v;
  }

  llvm::Value* ASTElement::loadValueIfNeeded(llvm::Value* value)
  {
    if (value->getType()->isPointerTy() &&
        value->getType() != context_.types().stringPtrType() &&
        value->getType() != context_.types().charPtrType())
    {
      return context_.builder().CreateLoad(value);
    }
    return value;
  }

  ASTElement::ASTElement(Context& context)
    : context_(context)
  {
  }

  ASTElement::~ASTElement(){

  };
}
