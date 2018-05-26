#include <AST/ASTLong.h>

namespace roe
{
  ASTLong::ASTLong(Context& context, int64_t value)
    : ASTElement(context)
    , value_(value)
  {
  }

  llvm::Value* ASTLong::evaluate()
  {
    return llvm::ConstantInt::get(context_.types().longType(), value_);
  }
}
