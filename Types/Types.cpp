#include <Module/Context.h>
#include <Module/ForwardDeclsImpl.h>
#include <Types/Types.h>

namespace roe
{
  void Types::init(Context& context)
  {
    auto* arrayType     = llvm::ArrayType::get(llvm::Type::getInt8Ty(context.native()), String::capacity);
    auto* stringLenType = llvm::Type::getInt8Ty(context.native());

    std::vector<llvm::Type*> structFieldTypes = {arrayType, stringLenType};

    stringType_    = llvm::StructType::create(context.native(), structFieldTypes, "string");
    stringPtrType_ = llvm::PointerType::get(stringType_, 0);
    charPtrType_   = llvm::PointerType::get(llvm::Type::getInt8Ty(context.native()), 0);
    longType_      = llvm::Type::getInt64Ty(context.native());
    longPtrType_   = llvm::PointerType::get(longType_, 0);
    boolType_      = llvm::Type::getInt1Ty(context.native());
    voidType_      = llvm::Type::getVoidTy(context.native());
    floatType_     = llvm::Type::getDoubleTy(context.native());
    floatPtrType_  = llvm::PointerType::get(floatType_, 0);

    rvalueToVarType_ = TypeMapping{{charPtrType_, stringType_},
                                   {stringPtrType_, stringType_},
                                   {longPtrType_, longType_},
                                   {longType_, longType_},
                                   {floatType_, floatType_}};

    valueTyToPointerTy_ =
      TypeMapping{{stringType_, stringPtrType_}, {longType_, longPtrType_}, {floatType_, floatPtrType_}};

    pointerTyToValueTy_ =
      TypeMapping{{stringPtrType_, stringType_}, {longPtrType_, longType_}, {floatPtrType_, floatType_}};
  }

  llvm::Type* Types::varTypeFromRVal(llvm::Type* val)
  {
    return resolveType(rvalueToVarType_, val);
  }

  llvm::Type* Types::poinerTyFromValTy(llvm::Type* val)
  {
    return resolveType(pointerTyToValueTy_, val);
  }

  llvm::Type* Types::resolveType(TypeMapping& mapping, llvm::Type* from)
  {
    auto fit = mapping.find(from);
    if (fit == mapping.end())
      return nullptr;
    return fit->second;
  }

  llvm::Type* Types::valTyFromPointerTy(llvm::Type* val)
  {
    return resolveType(this->valueTyToPointerTy_, val);
  }

  llvm::Type* Types::longType()
  {
    return longType_;
  }

  llvm::Type* Types::longPtrType()
  {
    return longPtrType_;
  }

  llvm::Type* Types::charPtrType()
  {
    return charPtrType_;
  }

  llvm::Type* Types::stringType()
  {
    return stringType_;
  }

  llvm::Type* Types::stringPtrType()
  {
    return stringPtrType_;
  }

  llvm::Type* Types::voidPtrType()
  {
    return charPtrType();
  };

  llvm::Type* Types::boolType()
  {
    return boolType_;
  };

  llvm::Type* Types::voidType()
  {
    return voidType_;
  };

  llvm::Type* Types::floatPtrType()
  {
    return floatPtrType_;
  };

  llvm::Type* Types::floatType()
  {
    return floatType_;
  };

  Types::Types(Context& context)
  {
    init(context);
  }
}
