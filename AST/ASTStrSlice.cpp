#include <AST/ASTStrSlice.h>
#include <Functions/FunctionRegistrar.h>

namespace roe
{

  ASTStrSlice::ASTStrSlice(Context& context, ASTElementPtr base,
                           ASTElementPtr from, ASTElementPtr len)
    : ASTElement(context)
    , base_(base)
    , len_(len)
    , from_(from)
  {
  }

  llvm::Value* ASTStrSlice::evaluate()
  {
    auto* varValue = base_->evaluate();
    auto* idx      = from_->evaluate();

    llvm::Value* out = nullptr;
    if (!len_)
    {
      out = context_.externalFunctions().makeCall(StringOps::GET_CHAR,
                                                  {varValue, idx});
    }
    else
    {
      auto* l = len_->evaluate();
      out = allocString();
      context_.externalFunctions().makeCall(StringOps::GET_SUBSTR,
                                            {varValue, idx, l, out});
    }

    return out;
  }
}
