#include <AST/ASTCStr.h>

namespace roe
{
  ASTCstr::ASTCstr(Context& context, const std::string& value)
    : ASTElement(context)
  {

    for(size_t idx = 0; idx < value.size(); ++idx)
    {
      char ch = value[idx];
      if (ch == '\\')
      {
        if (idx + 1 >= value.size())
        {
          throw ASTException() << "Invalid string " << value;
        }
        char* endP = nullptr;
        const char* nBegin = &value[idx + 1];
        auto res = std::strtol(nBegin, &endP, 10);

        auto nSize = endP - nBegin;
        if (!nSize)
        {
          throw ASTException() << "Invalid string " << value;
        }
         idx = idx + nSize;
         ch = static_cast<char>(res);
      }
      value_.push_back(ch);
    }

  }

  llvm::Value* ASTCstr::length() const
  {
    return llvm::ConstantInt::get(context_.types().longType(), value_.length());
  }

  llvm::Value* ASTCstr::evaluate()
  {
    auto& builder = context_.builder();
    return builder.CreateGlobalStringPtr(value_);
  }
}
