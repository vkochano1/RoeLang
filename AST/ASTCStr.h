#pragma once

#include <AST/ASTElement.h>

namespace roe
{

class ASTCstr: public ASTElement
{
public:
    ASTCstr(Context& context, const std::string& v);
    virtual llvm::Value* evaluate() override;
private:
   std::string value_; 
};

}
