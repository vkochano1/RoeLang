#include <AST/ASTDouble.h>


namespace roe
{
    ASTDouble::ASTDouble(Context& context, double value)
        : ASTElement(context)
        , value_(value)
    {
    }

    llvm::Value*  ASTDouble::evaluate()
    {
        auto& builder = context_.builder();
        return  llvm::ConstantInt::get(builder.getFloatTy(), value_);
    }
    
}
