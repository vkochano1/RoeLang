#include <Functions/FunctionRegistrar.h>
#include <Functions/StringOps.h>
#include <Module/Context.h>

namespace roe
{

  const std::string StringOps::CONCAT_STR_AND_STR     = "concatStrAndStr";
  const std::string StringOps::CONCAT_STR_AND_CHPTR   = "concatStrAndChPtr";
  const std::string StringOps::CONCAT_CHPTR_AND_STR   = "concatChPtrAndStr";
  const std::string StringOps::CONCAT_CHPTR_AND_CHPTR = "concatChPtrAndChPtr";

  const std::string StringOps::ASSIGN_CHPTR = "AssingFromCharPtr";
  const std::string StringOps::ASSIGN_STR   = "AssingFromStr";

  const std::string StringOps::EQUALS_STR_AND_STR   = "EqualsStrAndStr";
  const std::string StringOps::EQUALS_STR_AND_CHPTR = "EqualsStrAndCharPtr";
  const std::string StringOps::EQUALS_CHPTR_AND_STR = "EqualsCharPtrAndStr";
  const std::string StringOps::EQUALS_CHPTR_AND_CHPTR =
    "EqualsCharPtrAndCharPtr";

  const std::string StringOps::TO_INT_CHPTR = "CharPtrToInt";
  const std::string StringOps::TO_INT_STR   = "StrToInt";

  const std::string StringOps::INT_TO_STR    = "IntToStr";
  const std::string StringOps::DOUBLE_TO_STR = "DoubleToStr";

  const std::string StringOps::GET_CHAR   = "GetChar";
  const std::string StringOps::GET_SUBSTR = "GetSubstr";
  const std::string StringOps::GET_LENGTH = "GetLength";

  void StringOps::registerConcatBuiltins(Context& context)
  {
    context.externalFunctions().registerExternal(
      CONCAT_STR_AND_STR, &StringOps::concatStrAndStr,
      context.types().voidType(),
      {context.types().stringPtrType(), context.types().stringPtrType(),
       context.types().stringPtrType()});

    context.externalFunctions().registerExternal(
      CONCAT_STR_AND_CHPTR, &StringOps::concatStrAndCharPtr,
      context.types().voidType(),
      {context.types().stringPtrType(), context.types().charPtrType(), context.types().longType(),
       context.types().stringPtrType()});

    context.externalFunctions().registerExternal(
      CONCAT_CHPTR_AND_CHPTR, &StringOps::concatCharPtrAndCharPtr,
      context.types().voidType(),
      {context.types().charPtrType(), context.types().longType(), context.types().charPtrType()
      , context.types().longType(),
       context.types().stringPtrType()});

    context.externalFunctions().registerExternal(
      CONCAT_CHPTR_AND_STR, &StringOps::concatCharPtrAndStr,
      context.types().voidType(),
      {context.types().charPtrType(), context.types().longType(), context.types().stringPtrType(),
       context.types().stringPtrType()});
  }

  void StringOps::registerAssignBuiltins(Context& context)
  {
    context.externalFunctions().registerExternal(
      ASSIGN_STR, &StringOps::assignStr, context.types().voidType(),
      {context.types().stringPtrType(), context.types().stringPtrType()});

    context.externalFunctions().registerExternal(
      ASSIGN_CHPTR, &StringOps::assignChPtr, context.types().voidType(),
      {context.types().stringPtrType(), context.types().charPtrType(), context.types().longType()});
  }

  void StringOps::registerEqualsBuiltins(Context& context)
  {
    context.externalFunctions().registerExternal(
      EQUALS_STR_AND_STR, &StringOps::equalsStrAndStr,
      context.types().boolType(),
      {context.types().stringPtrType(), context.types().stringPtrType()});

    context.externalFunctions().registerExternal(
      EQUALS_STR_AND_CHPTR, &StringOps::equalsStrAndCharPtr,
      context.types().boolType(),
      {context.types().stringPtrType(), context.types().charPtrType(), context.types().longType()});

    context.externalFunctions().registerExternal(
      EQUALS_CHPTR_AND_STR, &StringOps::equalsCharPtrAndStr,
      context.types().boolType(),
      {context.types().charPtrType(), context.types().longType(), context.types().stringPtrType()});

    context.externalFunctions().registerExternal(
      EQUALS_CHPTR_AND_CHPTR, &StringOps::equalsCharPtrAndCharPtr,
      context.types().boolType(),
      {context.types().charPtrType(), context.types().longType()
        , context.types().charPtrType(), context.types().longType()});
  }

  void StringOps::registerConversionBuiltins(Context& context)
  {

    context.externalFunctions().registerExternal(
      StringOps::TO_INT_STR, &StringOps::stringToInt,
      context.types().longType(), {context.types().stringPtrType()});

    context.externalFunctions().registerExternal(
      StringOps::TO_INT_CHPTR, &StringOps::charPtrToInt,
      context.types().longType(), {context.types().charPtrType()});

    context.externalFunctions().registerExternal(
      StringOps::INT_TO_STR, &StringOps::intToString,
      context.types().voidType(),
      {context.types().longType(), context.types().stringPtrType()});

    context.externalFunctions().registerExternal(
      StringOps::DOUBLE_TO_STR, &StringOps::doubleToString,
      context.types().voidType(),
      {context.types().floatType(), context.types().stringPtrType()});

    context.externalFunctions().registerExternal(
      StringOps::GET_CHAR, &StringOps::getChar, context.types().longType(),
      {context.types().stringPtrType(), context.types().longType()});

    context.externalFunctions().registerExternal(
      StringOps::GET_SUBSTR, &StringOps::getSubstr, context.types().voidType(),
      {context.types().stringPtrType(), context.types().longType(),
       context.types().longType(), context.types().stringPtrType()});

       context.externalFunctions().registerExternal(
         StringOps::GET_LENGTH, &StringOps::getLength, context.types().longType(),
         {context.types().stringPtrType()});
  }

  void StringOps::registerBuiltins(Context& context)
  {
    registerConcatBuiltins(context);
    registerAssignBuiltins(context);
    registerEqualsBuiltins(context);
    registerConversionBuiltins(context);
  }

  static void concatImpl(StringOps::String_t* dest, const char* s1, size_t l1,
                         const char* s2, size_t l2)
  {
    std::memmove(&dest->data[0], s1, l1);
    std::memmove(&dest->data[l1], s2, l2);
    dest->len_             = l1 + l2;
    dest->data[dest->len_] = 0;
  }

  void StringOps::concatStrAndCharPtr(const StringOps::String_t* s1,
                                      const char* s2, int64_t len2, StringOps::String_t* out)
  {
    concatImpl(out, &s1->data[0], s1->len_, s2, len2);
  }

  void StringOps::concatStrAndStr(const StringOps::String_t* s1,
                                  const StringOps::String_t* s2,
                                  StringOps::String_t*       out)
  {
    concatImpl(out, &s1->data[0], s1->len_, &s2->data[0], s2->len_);
  }

  void
  StringOps::concatCharPtrAndStr(const char* s1, int64_t len1, const StringOps::String_t* s2,
                                 StringOps::String_t* out)
  {
    concatImpl(out, s1, len1, &s2->data[0], s2->len_);
  }

  void StringOps::concatCharPtrAndCharPtr(const char* s1, int64_t len1, const char* s2, int64_t len2,
                                          StringOps::String_t* out)
  {
    concatImpl(out, s1, len1, s2, len2);
  }

  //////////////////////////////////////////////////////////////////////////////////////

  // Assign
  void
  StringOps::assignStr(StringOps::String_t* s1, const StringOps::String_t* s2)
  {
    if (s1 != s2)
    {
      std::strncpy(&s1->data[0], &s2->data[0], s2->len_);
      s1->len_ = s2->len_;
    }
  }
  void StringOps::assignChPtr(String_t* s1, const char* s2 , int64_t len2)
  {
    std::strncpy(&s1->data[0], s2, len2);
    s1->len_ = len2;
  }

  // Equals
  static bool equals(const char* s1, size_t l1, const char* s2, size_t l2)
  {
    auto sx1 = std::string(s1, l1);
    auto sx2 = std::string(s2, l2);
    return sx1 == sx2;
  }

  bool StringOps::equalsStrAndCharPtr(const String_t* s1, const char* s2, int64_t len2)
  {
    return equals(s1->c_str(), s1->length(), s2, len2);
  }

  bool StringOps::equalsStrAndStr(const String_t* s1, const String_t* s2)
  {
    return equals(s1->c_str(), s1->length(), s2->c_str(), s2->length());
  }

  bool StringOps::equalsCharPtrAndStr(const char* s1, int64_t len1, const String_t* s2)
  {
    return equals(s1, len1, s2->c_str(), s2->length());
  }

  bool StringOps::equalsCharPtrAndCharPtr(const char* s1, int64_t len1, const char* s2, int64_t len2)
  {
    return equals(s1, len1, s2, len2);
  }

  void StringOps::intToString(int64_t i, String_t* s)
  {
    std::string tmp = std::to_string(i);
    s->len_         = tmp.length();
    std::memcpy(s->data, tmp.c_str(), tmp.length());
  }

  void StringOps::doubleToString(double d, String_t* s)
  {
    std::string tmp = std::to_string(d);
    s->len_         = tmp.length();
    std::memcpy(s->data, tmp.c_str(), tmp.length());
  }

  int64_t StringOps::stringToInt(const String_t* s)
  {
    char* endp = nullptr;
    return std::strtol(s->data, &endp, 10);
  }

  int64_t StringOps::charPtrToInt(const char* s)
  {
    char* endp = nullptr;
    return std::strtol(s, &endp, 10);
  }

  int64_t StringOps::getChar(const String_t* s, int64_t i)
  {
    return s->data[i];
  }

  int64_t StringOps::getLength(const String_t* s)
  {
    return s->len_;
  }

  void StringOps::getSubstr(const String_t* s, int64_t from, int64_t len,
                            String_t* out)
  {
    // std::cerr << "Called " << from << "  " << len << std::end;
    std::memcpy(&out->data[0], s->c_str() + from, len);
    out->data[len] = 0;
    out->len_      = len;
  }
}
