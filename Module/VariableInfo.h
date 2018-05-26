#pragma once

#include <Types/Types.h>

namespace roe
{
  class Context;

  class VariableInfo
  {
  public:
    VariableInfo(const std::string& name, Context& func, const llvm::Type*);

    VariableInfo();

    const std::string& name() const;

    const llvm::Value* value() const
    {
      return value_;
    }
    llvm::Value* value()
    {
      return value_;
    }
    llvm::Type* type()
    {
      return type_;
    }
    const llvm::Type* type() const
    {
      return type_;
    }

  private:
    std::string  name_;
    llvm::Value* value_;
    llvm::Type*  type_;
  };
}
