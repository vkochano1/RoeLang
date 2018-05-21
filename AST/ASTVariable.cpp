#include <AST/ASTVariable.h>
#include <Functions/FunctionRegistrar.h>
#include <boost/algorithm/string.hpp>

namespace roe
{

  const std::string ASTVariable::TAG_PREFIX   = "tag";
  const std::string ASTVariable::FIELD_PREFIX = "field";

  ASTVariable::ASTVariable(Context& context, const std::string& var)
    : ASTElement(context)
    , tag_(-1)
  {
    var_ = var;
    std::vector<std::string> varComponents;
    boost::split(varComponents, var_, boost::is_any_of("."));

    if (2 != varComponents.size())
    {
      return;
    }

    baseName_  = varComponents[0];
    fieldName_ = varComponents[1];

    isField_ = true;
  }

  bool ASTVariable::processContainerField()
  {
    if (fieldName_.find(TAG_PREFIX) == 0)
    {
      auto  tagStr = fieldName_.substr(TAG_PREFIX.length());
      char* endp   = nullptr;
      tag_         = std::strtol(tagStr.c_str(), &endp, 10);
      return true;
    }
    else if (fieldName_.find(FIELD_PREFIX) == 0)
    {
      auto fieldStr = fieldName_.substr(FIELD_PREFIX.length());

      auto containerConstraints = context_.rule().getContainerForParam(baseName_);
      if (!containerConstraints)
      {
        throw roe::ASTException() << "Couldn't resolve container for param";
      }
      tag_ = containerConstraints->getTagFromFieldName(fieldStr);
      return true;
    }

    return false;
  }

  size_t ASTVariable::tag() const
  {
    return tag_;
  }

  const std::string& ASTVariable::name() const
  {
    return var_;
  }

  const std::string& ASTVariable::baseName() const
  {
    return baseName_;
  }

  bool ASTVariable::isField() const
  {
    return isField_;
  }

  llvm::Value* ASTVariable::evaluateField()
  {
    processContainerField();
    auto& builder = context_.rule().builder();

    llvm::Value* result = allocString();
    llvm::Value* container = context_.rule().getParamValue(baseName());
    llvm::Value* tagVal = llvm::ConstantInt::get(context_.types().longType(), tag());

    context_.externalFunctions().makeCall(Bindings::GET_FIELD_STRING,
                                          {container, tagVal, result});
    return result;
  }

  llvm::Value* ASTVariable::evaluateLocalVar()
  {
    auto&        info   = context_.rule().getVariable(var_);
    llvm::Value* result = info.value();
    return result;
  }

  llvm::Value* ASTVariable::evaluate()
  {
    if (isField())
    {
      return evaluateField();
    }

    return evaluateLocalVar();
  }
}
