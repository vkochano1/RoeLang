#pragma once

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>
#include <unordered_map>
#include <StringOps.h>

namespace roe
{
 
    class Types
    {
    public:
         using TypeMapping = std::unordered_map<llvm::Type*,llvm::Type*>;
         using String = StringOps::String_t;
         
    public:
        static Types& instance();        
        void init(Context& context);
       
        llvm::Type* varTypeFromRVal(llvm::Type* val);
        llvm::Type* poinerTyFromValTy(llvm::Type* val);
        llvm::Type* valTyFromPointerTy(llvm::Type* val);
        llvm::Type* resolveType(TypeMapping& mapping, llvm::Type* from);

        Types();
        
    public:
        llvm::Type* longType();
        llvm::Type* longPtrType();
        
        llvm::Type* charPtrType();
        llvm::Type* voidPtrType ();
        
        llvm::Type* stringType();
        llvm::Type* stringPtrType();
        
        llvm::Type* boolType ();
        
    private:
        llvm::Type* longType_= nullptr;
        llvm::Type* longPtrType_= nullptr;
        llvm::Type* charPtrType_ = nullptr;
        llvm::Type* stringType_ = nullptr;
        llvm::Type* stringPtrType_ = nullptr;
        llvm::Type* voidPtrType_ = nullptr;
        llvm::Type* boolType_ = nullptr;
        
        TypeMapping  rvalueToVarType_;
        TypeMapping  pointerTyToValueTy_;
        TypeMapping  valueTyToPointerTy_;        
    };
    
    
}
