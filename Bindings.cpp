#include <Bindings.h>
#include <Context.h>
#include <FunctionRegistrar.h>

namespace roe
{

  int64_t IContainerAccess::getTagFromFieldName(const std::string& val)
  {
    return fieldNameToTagMapping_[val];
  }



void Bindings::registerBuiltins(Context& context)
{
    FunctionRegistrar::instance().registerExternal
    (
      context
    , "getField"
    ,&Bindings::getField
    , context.types().voidType()
    , {
           context.types().voidPtrType()
         , context.types().longType()
         , context.types().stringPtrType()
      }
    );

    FunctionRegistrar::instance().registerExternal
    (
      context
    , "setField"
    ,&Bindings::setField
    , context.types().voidType()
    , {
           context.types().voidPtrType()
         , context.types().longType()
         , context.types().stringPtrType()
      }
    );

    FunctionRegistrar::instance().registerExternal
    (
      context
    , "setFieldCharPtr"
    ,&Bindings::setFieldCharPtr
    , context.types().voidType()
    , {
           context.types().voidPtrType()
         , context.types().longType()
         , context.types().charPtrType()
      }
    );
}

void Bindings::getField(void* data, int64_t tag, StringOps::String_t* s)
{
    IContainerAccess* access = reinterpret_cast<IContainerAccess*> (data);
    access->getField(tag, *s);
}

void Bindings::setField(void* data, int64_t tag, StringOps::String_t* s)
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
