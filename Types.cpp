#include <Types.h>
#include <Context.h>

namespace roe 
{
    
Types& Types::instance()
{
    static Types instance_;
    return instance_;
}


void Types::init(Context& context)
{
    auto* arrayType = llvm::ArrayType::get(llvm::Type::getInt8Ty(context),String::size);
    auto* stringLenType = llvm::Type::getInt8Ty(context);
    std::vector<llvm::Type*> structFieldTypes = { arrayType, stringLenType};
    stringType_ = llvm::StructType::create(context, structFieldTypes, "string");

    stringPtrType_ = llvm::PointerType::get(stringType_,0);

    charPtrType_ = llvm::PointerType::get(llvm::Type::getInt8Ty(context),0);

    longType_ = llvm::Type::getInt32Ty(context);
    longPtrType_ = llvm::PointerType::get(longType_,0);

    boolType_ = llvm::Type::getInt1Ty(context);
    voidType_ = llvm::Type::getVoidTy(context);

    rvalueToVarType_ =   TypeMapping
    {
        {charPtrType_   , stringType_}
        ,{stringPtrType_ , stringType_}
        ,{longPtrType_   , longType_}
        ,{longType_   , longType_}

    };

    valueTyToPointerTy_ =   TypeMapping
    {
        {stringType_, stringPtrType_}
        ,{longType_ , longPtrType_}
    };

    pointerTyToValueTy_ = TypeMapping
    {
        {stringPtrType_   , stringType_}
        ,{longPtrType_ , longType_}
    };
}


llvm::Type* Types::varTypeFromRVal(llvm::Type* val)
{
    return resolveType(rvalueToVarType_, val);
}


llvm::Type* Types::poinerTyFromValTy(llvm::Type* val)
{
    return resolveType(pointerTyToValueTy_,val);
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


llvm::Type* Types::longType() {
    return longType_;
}


llvm::Type* Types::longPtrType() {
    return longPtrType_ ;
}


llvm::Type* Types::charPtrType() {
    return charPtrType_;
}


llvm::Type* Types::stringType() {
    return stringType_;
}


llvm::Type* Types::stringPtrType() {
    return stringPtrType_;
}

llvm::Type* Types::voidPtrType () 
{
    return charPtrType();
};

llvm::Type* Types::boolType () 
{
    return boolType_;
};


llvm::Type* Types::voidType () 
{
    return voidType_;
};


Types::Types()
{
}

}

