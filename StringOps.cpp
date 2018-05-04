#include <StringOps.h>
#include <Context.h>
#include <FunctionRegistrar.h>


namespace roe
{

const std::string StringOps::CONCAT_STR_AND_STR = "concatStrAndStr";
const std::string StringOps::CONCAT_STR_AND_CHPTR = "concatStrAndChPtr";
const std::string StringOps::CONCAT_CHPTR_AND_STR = "concatChPtrAndStr";
const std::string StringOps::CONCAT_CHPTR_AND_CHPTR = "concatChPtrAndChPtr";
 
const std::string StringOps::ASSIGN_CHPTR = "AssingFromCharPtr";
const std::string StringOps::ASSIGN_STR= "AssingFromStr";
   
const std::string StringOps::EQUALS_STR_AND_STR = "EqualsStrAndStr";
const std::string StringOps::EQUALS_STR_AND_CHPTR = "EqualsStrAndCharPtr";
const std::string StringOps::EQUALS_CHPTR_AND_STR = "EqualsCharPtrAndStr";
const std::string StringOps::EQUALS_CHPTR_AND_CHPTR = "EqualsCharPtrAndCharPtr";
   
const std::string StringOps::TO_INT_CHPTR = "CharPtrToInt";
const std::string StringOps::TO_INT_STR = "StrToInt";
const std::string StringOps::INT_TO_STR = "IntToStr";
    
void StringOps::registerConcatBuiltins(Context& context)
{
    
    FunctionRegistrar::instance().registerExternal
    (
      context
    , CONCAT_STR_AND_STR
    ,&StringOps::concatStrAndStr
    , Types::instance().voidType()
    , {  
           Types::instance().stringPtrType()
          ,Types::instance().stringPtrType()
          ,Types::instance().stringPtrType()
      }  
    );

    FunctionRegistrar::instance().registerExternal
    (
      context
    , CONCAT_STR_AND_CHPTR
    ,&StringOps::concatStrAndCharPtr
    , Types::instance().voidType()
    , {  
           Types::instance().stringPtrType()
          ,Types::instance().charPtrType()
          ,Types::instance().stringPtrType()
      }  
    );
    
   /* FunctionRegistrar::instance().registerExternal
    (
      context
    , CONCAT_CHPTR_AND_CHPTR
    ,&StringOps::concatCharPtrAndCharPtr
    , Types::instance().voidType()
    , {  
           Types::instance().charPtrType()
          ,Types::instance().charPtrType()
          ,Types::instance().stringPtrType()
      }  
    );*/
    
        FunctionRegistrar::instance().registerExternal
    (
      context
    , CONCAT_CHPTR_AND_STR
    ,&StringOps::concatCharPtrAndStr
    , Types::instance().voidType()
    , {  
           Types::instance().charPtrType()
          ,Types::instance().stringPtrType()
          ,Types::instance().stringPtrType()
      }  
    );
    

}

void StringOps::registerAssignBuiltins(Context& context)
{
    FunctionRegistrar::instance().registerExternal
    (
      context
    , ASSIGN_STR
    ,&StringOps::assignStr
    , Types::instance().voidType()
    , {  
          Types::instance().stringPtrType()
          ,Types::instance().stringPtrType()
      }  
    );
    
    
    FunctionRegistrar::instance().registerExternal
    (
      context
    , ASSIGN_CHPTR
    ,&StringOps::assignChPtr
    , Types::instance().voidType()
    , {  
           Types::instance().stringPtrType()
         , Types::instance().charPtrType()
          
      }  
    );
    
}


void StringOps::registerEqualsBuiltins(Context& context)
{
        FunctionRegistrar::instance().registerExternal
    (
      context
    , EQUALS_STR_AND_STR
    ,&StringOps::equalsStrAndStr
    , Types::instance().boolType()
    , {  
          Types::instance().stringPtrType()
        , Types::instance().stringPtrType()
      }  
    );

            FunctionRegistrar::instance().registerExternal
    (
      context
    , EQUALS_STR_AND_CHPTR
    ,&StringOps::equalsStrAndCharPtr
    , Types::instance().boolType()
    , {  
          Types::instance().stringPtrType()
        , Types::instance().charPtrType()
      }  
    );
    
            FunctionRegistrar::instance().registerExternal
    (
      context
    , EQUALS_CHPTR_AND_STR
    ,&StringOps::equalsStrAndStr
    , Types::instance().boolType()
    , {  
          Types::instance().charPtrType()
        , Types::instance().stringPtrType()
      }  
    );
    
            FunctionRegistrar::instance().registerExternal
    (
      context
    , EQUALS_CHPTR_AND_CHPTR
    ,&StringOps::equalsStrAndStr
    , Types::instance().boolType()
    , {  
          Types::instance().charPtrType()
        , Types::instance().charPtrType()
      }  
    );
    
    
}

void StringOps::registerConversionBuiltins(Context& context)
{
    
    FunctionRegistrar::instance().registerExternal
    (
      context
    , StringOps::TO_INT_STR
    ,&StringOps::stringToInt
    , Types::instance().longType()
    , {  
          Types::instance().stringPtrType()
      }  
    );

    FunctionRegistrar::instance().registerExternal
    (
      context
    , StringOps::TO_INT_CHPTR
    ,&StringOps::charPtrToInt
    , Types::instance().longType()
    , {  
          Types::instance().charPtrType()
      }  
    );
    
    FunctionRegistrar::instance().registerExternal
    (
      context
    , StringOps::INT_TO_STR
    ,&StringOps::intToString
    , Types::instance().voidType()
    , {  
        Types::instance().longType(),
        Types::instance().stringPtrType()
      }  
    );
}


void StringOps::registerBuiltins(Context& context)
{
    registerConcatBuiltins(context);
    registerAssignBuiltins(context);
    registerEqualsBuiltins(context);
    registerConversionBuiltins(context);
    
    FunctionRegistrar::instance().registerExternal
    (
      context
    , "ps"
    ,&StringOps::printString
    , Types::instance().voidType()
    , {  
          Types::instance().stringPtrType()
      }  
    );
    
}

static void  concatImpl(StringOps::String_t* dest, const char* s1, size_t l1, const char* s2, size_t l2 )
{
    std::memmove(&dest->data[0], s1, l1);
    std::memmove(&dest->data[l1], s2, l2);
    dest->len_ = l1 + l2;
    dest->data[dest->len_] = 0;
}

void StringOps::concatStrAndCharPtr(const StringOps::String_t* s1, const char* s2, StringOps::String_t* out)
{
    concatImpl(out, &s1->data[0], s1->len_, s2, std::strlen(s2));
}

void StringOps::concatStrAndStr(const StringOps::String_t* s1, const StringOps::String_t* s2, StringOps::String_t* out)
{
    concatImpl(out, &s1->data[0], s1->len_, &s2->data[0], s2->len_);
}

void  StringOps::concatCharPtrAndStr(const char* s1, const StringOps::String_t* s2, StringOps::String_t* out)
{
    concatImpl(out, s1, std::strlen(s1), &s2->data[0], s2->len_);
}

void  StringOps::concatCharPtrAndCharPtr(const char* s1, const char*s2, StringOps::String_t* out)
{
    concatImpl(out, s1, std::strlen(s1), s2, std::strlen(s2));
}

//////////////////////////////////////////////////////////////////////////////////////



 // Assign
    void StringOps::assignStr(StringOps::String_t* s1, const StringOps::String_t* s2)
    {
        if(s1 != s2)
        {
            std::strncpy(&s1->data[0], &s2->data[0], s2->len_);
            s1->len_ = s2->len_;
        }
    }
    void StringOps::assignChPtr(String_t* s1, const char* s2)
    {
        size_t len = std::strlen(s2);
        std::strncpy(&s1->data[0], s2, len);
        s1->len_ = len;
    }
    
    //Equals
    static bool equals(const char* s1, size_t l1,  const char* s2, size_t l2)
    {
        auto sx1 = std::string(s1, l1);
        auto sx2 = std::string(s2, l2);
        return sx1 == sx2;
    }

    bool StringOps::equalsStrAndCharPtr(const String_t* s1, const char* s2)
    {
        return equals(s1->c_str(), s1->length(), s2, std::strlen(s2));
    }
    
    bool StringOps::equalsStrAndStr(const String_t* s1, const String_t* s2)
    {
        return equals(s1->c_str(), s1->length(), s2->c_str(), s2->length());        
    }
    
    bool StringOps::equalsCharPtrAndStr(const char* s1, const String_t* s2)
    {
        return equals(s1, std::strlen(s1), s2->c_str(), s2->length());
    }
    
    bool StringOps::concatCharPtrAndCharPtr(const char* s1, const char*s2)
    {
        return equals(s1, std::strlen(s1), s2, std::strlen(s2));
    }

    void StringOps::printString(const String_t* s)
    {
        std::cout << std::string((char*)&s->data[0], s->len_) << std::endl;
    }

    void StringOps::intToString(int32_t i, String_t* s)
    {
        std::string tmp = std::to_string(i);
        s->len_= tmp.length();
        std::memcpy(s->data,tmp.c_str(), tmp.length()); 
    }
    
    int32_t StringOps::stringToInt(const String_t* s)
    {
        char* endp = nullptr;
        return std::strtol(s->data, &endp ,10);
    }
    
    int32_t StringOps::charPtrToInt(const char* s)
    {
        char* endp = nullptr;
        return std::strtol(s, &endp ,10);
    }


}


