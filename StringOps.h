#pragma once

#include <cstdint>
namespace roe
{

class Context;

class StringOps
{
public:
    struct String_t
    {
            static constexpr const int32_t size = 64;
            char data[size];
            int8_t len_;
    };
    
    static int32_t initString(String_t* s, const char* inited );
    static int32_t concat(String_t* s1, String_t* s2, String_t* sr);
    static bool equals(String_t* s1, String_t* s2);
    static int32_t concatSChPtr(String_t* s1, const char* s2, String_t* sr);
    static int32_t assign(String_t* s1, String_t* s2);
    static int32_t printString(String_t* s);
    static int32_t IntToString(int32_t, String_t* s);
    static int32_t StringToInt(String_t* s);
    static void registerBuilins(Context& ctx);
private:
    
};
}
