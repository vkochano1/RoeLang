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
    virtual void  setField(int32_t tag, const StringOps::String_t& value) = 0;
    virtual void  setField(int32_t tag, const char* value, size_t len) = 0;
    virtual void  getField(int32_t tag, StringOps::String_t& value) = 0;
};

class ContainerAccess : public IContainerAccess
{
public:
    virtual void  setField(int32_t tag, const StringOps::String_t& value)
    {
     data_ [tag] = std::string(value.data, value.len_);   
    }
    
    virtual void  setField(int32_t tag, const char* value, size_t len)
    {
     data_ [tag] = std::string(value, len);   
    }
    
    virtual void  getField(int32_t tag, StringOps::String_t& value)
    {
        std::string& val =  data_[tag];
        if (val.length() == 0)
        {
            value.len_ = 0;
            return;
        }
        std::strncpy(&value.data[0], &val[0], val.length());
        value.len_ = val.length();
    }
    
    void dump(std::ostream& ostrm) const 
    {
        for ( const auto& p : data_)
        {
            ostrm << p.first <<  " -> " << p.second << std::endl;
        }
    }
    
public:
    std::unordered_map<int32_t, std::string>  data_; 
};

class Bindings
{
public:        
    static int32_t getField(void*, int32_t tag, StringOps::String_t* s);
    static int32_t setField(void*, int32_t tag, StringOps::String_t* s); 
    static int32_t setFieldCharPtr(void*, int32_t tag, const char* s); 
    static void registerBuiltins(Context& ctx);
};  
}

