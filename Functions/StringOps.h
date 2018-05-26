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

    static const std::string TO_DOUBLE_CHPTR;
    static const std::string TO_DOUBLE_STR;

    static const std::string INT_TO_STR;
    static const std::string DOUBLE_TO_STR;
    static const std::string GET_CHAR;
    static const std::string GET_LENGTH;
    static const std::string GET_SUBSTR;

    struct String_t
    {
      static constexpr const int64_t size = 64;
      char                           data[size];
      int8_t                         len_;

      const int8_t& length() const
      {
        return len_;
      }
      int8_t& length()
      {
        return len_;
      }
      const char* c_str() const
      {
        return &data[0];
      }
      char* data_ptr()
      {
        return &data[0];
      }
    };

    // Concat
    static void concatStrAndCharPtr(const String_t* s1, const char* s2, int64_t len2, String_t* out);
    static void concatStrAndStr(const String_t* s1, const String_t* s2, String_t* out);
    static void concatCharPtrAndStr(const char* s1, int64_t len1, const String_t* s2, String_t* out);
    static void concatCharPtrAndCharPtr(const char* s1, int64_t len1, const char* s2, int64_t len2, String_t* out);

    // Assign
    static void assignStr(String_t* s1, const String_t* s2);
    static void assignChPtr(String_t* s1, const char* s2, int64_t len2);

    // Equals
    static bool equalsStrAndCharPtr(const String_t* s1, const char* s2, int64_t len2);
    static bool equalsStrAndStr(const String_t* s1, const String_t* s2);
    static bool equalsCharPtrAndStr(const char* s1, int64_t len2, const String_t* s2);
    static bool equalsCharPtrAndCharPtr(const char* s1, int64_t len1, const char* s2, int64_t len2);

    static void intToString(int64_t, String_t* s);
    static void doubleToString(double, String_t* s);

    // Cnnversions
    static int64_t charPtrToInt(const char* s);
    static int64_t stringToInt(const String_t* s);
    static double charPtrToDouble(const char* s);
    static double stringToDouble(const String_t* s);

    // Substr
    static int64_t getChar(const String_t* s, int64_t);
    static void getSubstr(const String_t* s, int64_t from, int64_t len, String_t* out);
    static int64_t getLength(const String_t* s);

  public:
    static void registerBuiltins(Context& ctx);
    static void registerConcatBuiltins(Context& ctx);
    static void registerAssignBuiltins(Context& ctx);
    static void registerEqualsBuiltins(Context& ctx);
    static void registerConversionBuiltins(Context& ctx);
  };
}
