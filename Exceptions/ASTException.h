#pragma once
#include <Exceptions/ExceptionBase.h>

namespace roe
{
  class ASTException : public ExceptionBase
  {
  public:
    ASTException()
      : ExceptionBase("ASTException:")
    {
    }
  };
}
