#pragma once
#include <Functions/StringOps.h>
#include <unordered_map>
#include <cstring>
#include <iostream>

namespace roe
{
class Context;


class IContainerAccess
{
public:
  using FieldNameToTagMapping = std::unordered_map<std::string, int64_t>;
public:
  int64_t getTagFromFieldName(const std::string& val);

public:
    virtual void  setField(int64_t tag, const StringOps::String_t& value) = 0;
    virtual void  setField(int64_t tag, const char* value, size_t len) = 0;
    virtual void  getField(int64_t tag, StringOps::String_t& value) = 0;

protected:
    FieldNameToTagMapping fieldNameToTagMapping_;
};


class Bindings
{
public:
  static const std::string PRINT_STR;
  static const std::string PRINT_INT;
  static const std::string PRINT_DOUBLE;

  static const std::string GET_FIELD_STRING;
  static const std::string SET_FIELD_STRING;
  static const std::string SET_FIELD_CHPTR;

public:
  static void getFieldString(void*, int64_t tag, StringOps::String_t* s);
  static void setFieldString(void*, int64_t tag, StringOps::String_t* s);
  static void setFieldCharPtr(void*, int64_t tag, const char* s);

  // Print
  static void  printString(const StringOps::String_t* s);
  static void  printInt(int64_t);
  static void  printDouble(double);

  static void registerBuiltins(Context& ctx);
};
}
