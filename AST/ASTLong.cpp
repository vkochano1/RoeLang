#include <AST/ASTLong.h>

namespace roe
{
    ASTLong::ASTLong(Context& context, int32_t value)
    : ASTElement(context)
    , value_(value)
    {
    }
    
    llvm::Value* ASTLong::evaluate()
    {
        auto& builder = context_.builder();
        return  llvm::ConstantInt::get(Types::instance().longType(), value_);
    }

}

