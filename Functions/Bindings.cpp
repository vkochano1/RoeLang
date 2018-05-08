#include <Functions/Bindings.h>
#include <Module/Context.h>
#include <Functions/FunctionRegistrar.h>

namespace roe
{

  const std::string Bindings::PRINT_STR = "printString";
  const std::string Bindings::PRINT_INT = "printLong";
  const std::string Bindings::PRINT_DOUBLE = "printDouble";

  const std::string Bindings::GET_FIELD_STRING= "getFieldString";;
  const std::string Bindings::SET_FIELD_STRING = "setFieldString";
  const std::string Bindings::SET_FIELD_CHPTR = "setFieldCharPtr";


int64_t IContainerAccess::getTagFromFieldName(const std::string& val)
{
  return fieldNameToTagMapping_[val];
}

void Bindings::registerBuiltins(Context& context)
{
    context.externalFunctions().registerExternal
    (
    GET_FIELD_STRING
    ,&Bindings::getFieldString
    , context.types().voidType()
    , {
           context.types().voidPtrType()
         , context.types().longType()
         , context.types().stringPtrType()
      }
    );

    context.externalFunctions().registerExternal
    (
     SET_FIELD_STRING
    ,&Bindings::setFieldString
    , context.types().voidType()
    , {
           context.types().voidPtrType()
         , context.types().longType()
         , context.types().stringPtrType()
      }
    );

    context.externalFunctions().registerExternal
    (
     SET_FIELD_CHPTR
    ,&Bindings::setFieldCharPtr
    , context.types().voidType()
    , {
           context.types().voidPtrType()
         , context.types().longType()
         , context.types().charPtrType()
      }
    );

    context.externalFunctions().registerExternal
    (
     PRINT_STR
    ,&Bindings::printString
    , context.types().voidType()
    , {
          context.types().stringPtrType()
      }
    );

    context.externalFunctions().registerExternal
    (
     PRINT_INT
    ,&Bindings::printInt
    , context.types().voidType()
    , {
          context.types().longType()
      }
    );

    context.externalFunctions().registerExternal
    (
     PRINT_DOUBLE
    ,&Bindings::printDouble
    , context.types().voidType()
    , {
          context.types().floatType()
      }
    );

}

void Bindings::printString(const StringOps::String_t* s)
{
    std::cout << std::string((char*)&s->data[0], s->len_) << std::endl;
}

void  Bindings::printInt(int64_t i)
{
  std::cout << i << std::endl;
}

void  Bindings::printDouble(double d)
{
  std::cout << d << std::endl;
}

void Bindings::getFieldString(void* data, int64_t tag, StringOps::String_t* s)
{
    IContainerAccess* access = reinterpret_cast<IContainerAccess*> (data);
    access->getField(tag, *s);
}

void Bindings::setFieldString(void* data, int64_t tag, StringOps::String_t* s)
{
    IContainerAccess* access = reinterpret_cast<IContainerAccess*> (data);
    access->setField(tag, *s);
}

void Bindings::setFieldCharPtr(void* data, int64_t tag, const char* str)
{
    IContainerAccess* access = reinterpret_cast<IContainerAccess*> (data);
    access->setField(tag, str, strlen(str));
}

}
