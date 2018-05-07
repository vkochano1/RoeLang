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
        return  llvm::ConstantFP::get(context_.types().floatType(), value_);
    }
    
}
