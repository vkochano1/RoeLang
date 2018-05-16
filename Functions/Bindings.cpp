#include <Functions/Bindings.h>
#include <Functions/FunctionRegistrar.h>
#include <Module/Context.h>
#include <AST/ASTException.h>

namespace roe
{

  const std::string Bindings::PRINT_STR    = "printString";
  const std::string Bindings::PRINT_INT    = "printLong";
  const std::string Bindings::PRINT_DOUBLE = "printDouble";

  const std::string Bindings::GET_FIELD_STRING = "getFieldString";
  ;
  const std::string Bindings::SET_FIELD_STRING = "setFieldString";
  const std::string Bindings::SET_FIELD_CHPTR  = "setFieldCharPtr";
  const std::string Bindings::SET_FIELD_INT    = "setFieldInt";
  const std::string Bindings::SET_FIELD_DOUBLE = "setFieldDouble";

  int64_t IContainerAccess::getTagFromFieldName(const std::string& val)
  {
    auto fit = fieldNameToTagMapping_.find(val);
    if (fit == fieldNameToTagMapping_.end())
    {
      throw ASTException("Invalid fieldName");
    }

    return fit->second;
  }

  void Bindings::registerBuiltins(Context& context)
  {
    context.externalFunctions().registerExternal(
      GET_FIELD_STRING, &Bindings::getFieldString, context.types().voidType(),
      {context.types().voidPtrType(), context.types().longType(),
       context.types().stringPtrType()});

    context.externalFunctions().registerExternal(
      SET_FIELD_STRING, &Bindings::setFieldString, context.types().voidType(),
      {context.types().voidPtrType(), context.types().longType(),
       context.types().stringPtrType()});

    context.externalFunctions().registerExternal(
      SET_FIELD_CHPTR, &Bindings::setFieldCharPtr, context.types().voidType(),
      {context.types().voidPtrType(), context.types().longType(),
       context.types().charPtrType(), context.types().longType()});

    context.externalFunctions().registerExternal(
      SET_FIELD_INT, &Bindings::setFieldInt, context.types().voidType(),
      {context.types().voidPtrType(), context.types().longType(),
       context.types().longType()});
    context.externalFunctions().registerExternal(
      SET_FIELD_DOUBLE, &Bindings::setFieldDouble, context.types().voidType(),
      {context.types().voidPtrType(), context.types().longType(),
       context.types().floatType()});

    context.externalFunctions().registerExternal(
      PRINT_STR, &Bindings::printString, context.types().voidType(),
      {context.types().stringPtrType()});

    context.externalFunctions().registerExternal(PRINT_INT, &Bindings::printInt,
                                                 context.types().voidType(),
                                                 {context.types().longType()});

    context.externalFunctions().registerExternal(
      PRINT_DOUBLE, &Bindings::printDouble, context.types().voidType(),
      {context.types().floatType()});
  }

  void Bindings::printString(const StringOps::String_t* s)
  {
    std::cout << std::string((char*)&s->data[0], s->len_) << std::endl;
  }

  void Bindings::printInt(int64_t i) { std::cout << i << std::endl; }

  void Bindings::printDouble(double d) { std::cout << d << std::endl; }

  void Bindings::getFieldString(void* data, int64_t tag, StringOps::String_t* s)
  {
    IContainerAccess* access = reinterpret_cast<IContainerAccess*>(data);
    access->getField(tag, *s);
  }

  void Bindings::setFieldString(void* data, int64_t tag, StringOps::String_t* s)
  {
    IContainerAccess* access = reinterpret_cast<IContainerAccess*>(data);
    access->setField(tag, *s);
  }

  void Bindings::setFieldCharPtr(void* data, int64_t tag, const char* str, int64_t len)
  {
    IContainerAccess* access = reinterpret_cast<IContainerAccess*>(data);
    access->setField(tag, str, len);
  }

  void Bindings::setFieldInt(void* data, int64_t tag, int64_t val)
  {
    IContainerAccess* access = reinterpret_cast<IContainerAccess*>(data);
    access->setField(tag, val);
  }

  void Bindings::setFieldDouble(void* data, int64_t tag, double val)
  {
    IContainerAccess* access = reinterpret_cast<IContainerAccess*>(data);
    access->setField(tag, val);
  }
}
