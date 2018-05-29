#include <AST/ASTReturn.h>

namespace roe
{
  ASTReturn::ASTReturn(Context& context)
    : ASTElement(context)
  {
  }

  llvm::Value* ASTReturn::evaluate()
  {
    auto& builder = context_.builder();
    builder.CreateRetVoid();
    throw ReturnNotification();
  }
}
