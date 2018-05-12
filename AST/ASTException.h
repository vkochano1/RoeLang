#pragma once
#include <exception>
#include <string>

namespace roe
{

  class ASTException : std::exception
  {
  public:
    ASTException(const std::string& text)
      : text_(text)
    {
    }

    const char* what() const noexcept override { return text_.c_str(); }

  private:
    std::string text_;
  };
}
