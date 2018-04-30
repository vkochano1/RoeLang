#include <Bindings.h>
#include <Context.h>
#include <FunctionRegistrar.h>

namespace roe
{
 
void Bindings::registerBuiltins(Context& context)
{
    FunctionRegistrar::instance().registerExternal
    (
      context
    , "getField"
    ,&Bindings::getField
    , Types::instance().longType()
    , { 
           Types::instance().voidPtrType()
         , Types::instance().longType()
         , Types::instance().stringPtrType()
      }  
    );
    
    FunctionRegistrar::instance().registerExternal
    (
      context
    , "setField"
    ,&Bindings::setField
    , Types::instance().longType()
    , {  
           Types::instance().voidPtrType()
         , Types::instance().longType()
         , Types::instance().stringPtrType()
      }  
    );

    FunctionRegistrar::instance().registerExternal
    (
      context
    , "setFieldCharPtr"
    ,&Bindings::setFieldCharPtr
    , Types::instance().longType()
    , {  
           Types::instance().voidPtrType()
         , Types::instance().longType()
         , Types::instance().charPtrType()
      }  
    );
}


int Bindings::getField(void* data, int32_t tag, StringOps::String_t* s)
{
    IContainerAccess* access = reinterpret_cast<IContainerAccess*> (data);
    access->getField(tag, *s);
    return 0;
}

int Bindings::setField(void* data, int32_t tag, StringOps::String_t* s)
{
    IContainerAccess* access = reinterpret_cast<IContainerAccess*> (data);
    access->setField(tag, *s);
    return 0;
}

int Bindings::setFieldCharPtr(void* data, int32_t tag, const char* str)
{
    IContainerAccess* access = reinterpret_cast<IContainerAccess*> (data);
    access->setField(tag, str, strlen(str));
    return 0;
}

    
}
