#include <Module/Context.h>
#include <Module/ForwardDeclsImpl.h>
#include <Module/VariableInfo.h>

namespace roe
{
  VariableInfo::VariableInfo(const std::string& name, Context& context, const llvm::Type* type)
    : name_(name)
  {
    auto* cur = context.builder().GetInsertBlock();
    context.builder().SetInsertPoint(context.rule().localsBlock());
    value_ = context.builder().CreateAlloca(const_cast<llvm::Type*>(type));
    context.builder().SetInsertPoint(cur);
  }

  VariableInfo::VariableInfo()
  {
  }

  const std::string& VariableInfo::name() const
  {
    return name_;
  }
}
