#pragma once

#include <AST/ASTElement.h>

namespace roe
{
  class ASTFunctionCall : public ASTElement
  {
  public:
    static const std::string TO_STRING_BUILTIN;
    static const std::string TO_INT_BUILTIN;
    static const std::string TO_DOUBLE_BUILTIN;
    static const std::string PRINT_BUILTIN;
    static const std::string LENGTH_BUILTIN;

  public:
    ASTFunctionCall(Context& context, const std::string& name, ASTElementPtr args);
    virtual llvm::Value* evaluate() override;
    ~ASTFunctionCall();

  protected:
    bool isBuiltInFunction() const;
    bool processBuiltins(llvm::Value*& retValue);
    bool processModuleFunction(llvm::Value*& retValue);
    bool processRegularFunction(llvm::Value*& retValue);

  private:
    std::string                 name_;
    std::shared_ptr<ASTElement> args_;
  };
}
