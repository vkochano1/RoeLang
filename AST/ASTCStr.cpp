#include <AST/ASTCStr.h>

namespace roe
{

  ASTCstr::ASTCstr(Context& context, const std::string& v)
    : ASTElement(context)
    , value_(v)
  {
  }

  llvm::Value* ASTCstr::evaluate()
  {
    auto& builder = context_.builder();
    return builder.CreateGlobalStringPtr(value_);
  }
}
