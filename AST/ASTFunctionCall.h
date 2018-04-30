#pragma once

#include <AST/ASTElement.h>

namespace roe
{


class ASTFunctionCall : public ASTElement
{
public:
    ASTFunctionCall(Context& context, const std::string& name, ASTElementPtr args);
    virtual llvm::Value* evaluate() override;
    ~ASTFunctionCall();
protected:
    llvm::Value* processBuiltins();
private:
   std::string name_; 
   std::shared_ptr<ASTElement> args_;
};


}
