#include <AST/ASTCStr.h>

namespace roe
{

  ASTCstr::ASTCstr(Context& context, const std::string& value)
    : ASTElement(context)
    , value_(value)
  {
  }

  llvm::Value* ASTCstr::evaluate()
  {
    auto& builder = context_.builder();
    return builder.CreateGlobalStringPtr(value_);
  }
}
