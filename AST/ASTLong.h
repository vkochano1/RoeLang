#pragma once

#include <AST/ASTElement.h>

namespace roe
{

class ASTLong: public ASTElement
{
public:
    ASTLong(Context& context, int32_t value);    
    virtual llvm::Value* evaluate() override;
private:
   int32_t value_; 
};

}


