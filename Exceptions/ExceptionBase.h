#pragma once

#include <exception>
#include <iostream>
#include <sstream>
#include <string>

namespace roe
{
  class ExceptionBase : public std::exception
  {
  public:
    ExceptionBase(const std::string& text = "")
    {
      if (text.length())
        ostrm_ << text;
    }
    ExceptionBase(const ExceptionBase& exception)
    {
      ostrm_ << exception.ostrm_.str();
    }

    template<typename T>
    ExceptionBase& operator<<(const T& val)
    {
      ostrm_ << val;
      return *this;
    }

    const char* what() const noexcept override
    {
      out_ = ostrm_.str().c_str();
      return out_.c_str();
    }

  private:
    std::ostringstream  ostrm_;
    mutable std::string out_;
  };
}
