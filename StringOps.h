#pragma once

#include <cstdint>
#include <string>

namespace roe
{

class Context;

class StringOps
{
public:
    static const std::string CONCAT_STR_AND_STR;
    static const std::string CONCAT_STR_AND_CHPTR;
    static const std::string CONCAT_CHPTR_AND_STR;
    static const std::string CONCAT_CHPTR_AND_CHPTR;
    
    
    static const std::string ASSIGN_CHPTR;
    static const std::string ASSIGN_STR;
   
    static const std::string EQUALS_STR_AND_STR;
    static const std::string EQUALS_STR_AND_CHPTR;
    static const std::string EQUALS_CHPTR_AND_STR;
    static const std::string EQUALS_CHPTR_AND_CHPTR;
   
    
    static const std::string TO_INT_CHPTR;
    static const std::string TO_INT_STR;
    static const std::string INT_TO_STR;
 
    struct String_t
    {
            static constexpr const int32_t size = 64;
            char data[size];
            int8_t len_;                                                                                                                               
            
            int8_t length() const  {return len_;}
            const char* c_str() const  {return &data[0];}
 
    };
    
    // Concat
    static void concatStrAndCharPtr(const String_t* s1, const char* s2, String_t* out);
    static void concatStrAndStr(const String_t* s1, const String_t* s2, String_t* out);
    static void concatCharPtrAndStr(const char* s1, const String_t* s2, String_t* out);
    static void concatCharPtrAndCharPtr(const char* s1, const char*s2, String_t* out);
    
    // Assign
    static void assignStr(String_t* s1, const String_t* s2);
    static void assignChPtr(String_t* s1, const char* s2);
    
    //Equals
    static bool equalsStrAndCharPtr(const String_t* s1, const char* s2);
    static bool equalsStrAndStr(const String_t* s1, const String_t* s2);
    static bool equalsCharPtrAndStr(const char* s1, const String_t* s2);
    static bool concatCharPtrAndCharPtr(const char* s1, const char*s2);
    
    static void intToString(int32_t, String_t* s);

    // Cnnversions
    static int32_t charPtrToInt(const char* s);
    static int32_t stringToInt(const String_t* s);
   
    static void  printString(const String_t* s);

public:
    static void registerBuiltins(Context& ctx);
  
    static void registerConcatBuiltins(Context& ctx);
    static void registerAssignBuiltins(Context& ctx);
    static void registerEqualsBuiltins(Context& ctx);
    static void registerConversionBuiltins(Context& ctx);
    
private:
    
};
}
