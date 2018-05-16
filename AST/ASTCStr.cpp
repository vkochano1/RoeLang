#include <AST/ASTCStr.h>

namespace roe
{

  ASTCstr::ASTCstr(Context& context, const std::string& value)
    : ASTElement(context)
    , value_(value)
  {
  }

  llvm::Value* ASTCstr::length() const
  {
    return llvm::ConstantInt::get(context_.types().longType(), value_.length());
  }

  llvm::Value* ASTCstr::evaluate()
  {
    auto& builder = context_.builder();
    return builder.CreateGlobalStringPtr(value_);
  }
}
