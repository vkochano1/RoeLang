#include <StringOps.h>
#include <Context.h>
#include <FunctionRegistrar.h>

namespace roe
{

void StringOps::registerBuilins(Context& context)
{
    FunctionRegistrar::instance().registerExternal
    (
      context
    , "inits"
    ,&StringOps::initString
    , Types::instance().longType()
    , {  
          Types::instance().stringPtrType()
        , Types::instance().charPtrType()
      }  
    );
    
    FunctionRegistrar::instance().registerExternal
    (
      context
    , "equals"
    ,&StringOps::equals
    , Types::instance().boolType()
    , {  
          Types::instance().stringPtrType()
        , Types::instance().stringPtrType()
      }  
    );
    
    FunctionRegistrar::instance().registerExternal
    (
      context
    , "concat"
    ,&StringOps::concat
    , Types::instance().longType()
    , {  
          Types::instance().stringPtrType()
          ,Types::instance().stringPtrType()
          ,Types::instance().stringPtrType()
      }  
    );
   
     FunctionRegistrar::instance().registerExternal
    (
      context
    , "concatSCHPtr"
    ,&StringOps::concatSChPtr
   
    , Types::instance().longType()
    , {  
          Types::instance().stringPtrType()
          ,Types::instance().charPtrType()
          ,Types::instance().stringPtrType()
      }  
    );
   
    
    
    FunctionRegistrar::instance().registerExternal
    (
      context
    , "assign"
    ,&StringOps::assign
    , Types::instance().longType()
    , {  
          Types::instance().stringPtrType()
          ,Types::instance().stringPtrType()
      }  
    );
    
       FunctionRegistrar::instance().registerExternal
    (
      context
    , "ps"
    ,&StringOps::printString
    , Types::instance().longType()
    , {  
          Types::instance().stringPtrType()
      }  
    );
    
    FunctionRegistrar::instance().registerExternal
    (
      context
    , "int"
    ,&StringOps::StringToInt
    , Types::instance().longType()
    , {  
          Types::instance().stringPtrType()
      }  
    );
    
     FunctionRegistrar::instance().registerExternal
    (
      context
    , "str"
    ,&StringOps::IntToString
    , Types::instance().longType()
    , {  
        Types::instance().longType(),
          Types::instance().stringPtrType()
      }  
    );
}


int StringOps::printString(String_t* s)
{
    std::cout << std::string((char*)&s->data[0], s->len_) << std::endl;
    return 0;
}

int StringOps::initString(String_t* s, const char* inited)
{
    s->len_=std::strlen(inited);
    std::strncpy(&s->data[0], inited, s->len_);
    return 0;
}

int32_t StringOps::concat(String_t* s1, String_t* s2, String_t* sr)
{
    char tmp [64];
    std::memcpy((void*)&tmp[0], (void*)&s1->data[0], s1->len_);
    std::memcpy((void*)&tmp[s1->len_], (void*)&s2->data[0], s2->len_);
    sr->len_ = s1->len_ + s2->len_;
   
    std::memcpy((void*)&sr->data[0], (void*)&tmp[0], sr->len_);
    tmp[sr->len_] = 0;
     
    return 0;
}

int32_t StringOps::concatSChPtr(String_t* s1, const char* s2, String_t* sr)
{
    std::strncpy(&sr->data[0], &s1->data[0], s1->len_);
    std::strncpy(&sr->data[s1->len_], s2, strlen(s2));
    sr->len_ = s1->len_ + strlen(s2);
    return 0;
}

int32_t StringOps::assign( String_t* sr, String_t* s1)
{
    std::strncpy(&sr->data[0], &s1->data[0], s1->len_);
    sr->len_ = s1->len_;
    return 0;
}

bool StringOps::equals( String_t* sr, String_t* s1)
{
    auto sx1 = std::string(&sr->data[0], sr->len_);
    auto sx2 = std::string(&s1->data[0], s1->len_);
    

    return sx1 == sx2;
    return  0 == std::strcmp(&sr->data[0], &s1->data[0]);
}

int32_t StringOps::IntToString(int32_t i, String_t* s)
{
    std::string tmp = std::to_string(i);
    s->len_= tmp.length();
    std::memcpy(s->data,tmp.c_str(), tmp.length()); 
    return 0;
}
    
int32_t StringOps::StringToInt(String_t* s)
{
    char* endp = nullptr;
    return std::strtol(s->data, &endp ,10);
}

}


