#include <AST/ASTBlock.h>

namespace roe
{
  ASTBlock::ASTBlock(Context& context)
    : ASTElement(context)
  {
  }

  llvm::Value* ASTBlock::evaluate()
  {
    for (auto& blockElement : elements_)
    {
      blockElement->evaluate();
    }
    return nullptr;
  }

  void ASTBlock::addElement(ASTElementPtr element)
  {
    elements_.push_back(element);
  }
}
