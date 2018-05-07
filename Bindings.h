#pragma once
#include <StringOps.h>
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
    static void getField(void*, int64_t tag, StringOps::String_t* s);
    static void setField(void*, int64_t tag, StringOps::String_t* s);
    static void setFieldCharPtr(void*, int64_t tag, const char* s);
    static void registerBuiltins(Context& ctx);
};
}
