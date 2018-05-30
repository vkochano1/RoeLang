#pragma once
#include <Functions/StringOps.h>
#include <cstring>
#include <iostream>
#include <unordered_map>

namespace roe
{
  class Context;

  class IContainerAccess
  {
  public:
    virtual void setField(int64_t tag, const StringOps::String_t& value) = 0;
    virtual void setField(int64_t tag, int64_t value)                    = 0;
    virtual void setField(int64_t tag, double value)                     = 0;
    virtual void setField(int64_t tag, const char* value, size_t len) = 0;
    virtual void getField(int64_t tag, StringOps::String_t& value) = 0;

  public:
    virtual ~IContainerAccess(){};
  };

  class IPrinter
  {
  public:
    virtual void print(const StringOps::String_t* s) = 0;
    virtual void print(int64_t)                      = 0;
    virtual void print(double)                       = 0;
    virtual void print(const char*)                  = 0;

  public:
    virtual ~IPrinter(){};
  };

  class IConstraints
  {
  public:
    using FieldNameToTagMapping = std::unordered_map<std::string, int64_t>;

  public:
    virtual int64_t getTagFromFieldName(const std::string& fieldName) const;
    virtual bool longAssignmentAllowed() const  {return false;}
    virtual bool doubleAssignmentAllowed() const  {return false;}
    virtual bool stringAssignmentAllowed() const  {return true;}  

    virtual ~IConstraints()
    {
    }

  protected:
    FieldNameToTagMapping fieldNameToTagMapping_;
  };

  class Bindings
  {
  public:
    static const std::string PRINT_STR;
    static const std::string PRINT_CSTR;
    static const std::string PRINT_INT;
    static const std::string PRINT_DOUBLE;

    static const std::string GET_FIELD_STRING;
    static const std::string SET_FIELD_STRING;
    static const std::string SET_FIELD_CHPTR;
    static const std::string SET_FIELD_INT;
    static const std::string SET_FIELD_DOUBLE;
    static const std::string SET_STR_CHAR;
  public:
    static void getFieldString(void*, int64_t tag, StringOps::String_t* s);
    static void setFieldString(void*, int64_t tag, StringOps::String_t* s);
    static void setFieldCharPtr(void*, int64_t tag, const char* s, int64_t len);
    static void setFieldInt(void*, int64_t tag, int64_t val);
    static void setFieldDouble(void*, int64_t tag, double val);
    static void setStrChar(StringOps::String_t* s, int64_t val, int64_t idx);

    // Print
    static void printString(void*, const StringOps::String_t* s);
    static void printInt(void*, int64_t);
    static void printDouble(void*, double);
    static void printCStr(void*, const char*);

    static void registerBuiltins(Context& ctx);
  };
}
