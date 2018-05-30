#pragma once

#include <RoeLangLib/Loader.h>
#include <iostream>

namespace roe
{
  namespace test
  {
    class DummyConstraints : public IConstraints
    {
    public:
      virtual bool longAssignmentAllowed() const  {return true;}
      virtual bool doubleAssignmentAllowed() const  {return true;}
      virtual bool stringAssignmentAllowed() const  {return true;}
      DummyConstraints();
    };

    class DummyContainer : public roe::IContainerAccess
    {
    public:
      virtual void setField(int64_t tag, const StringOps::String_t& value) override;
      virtual void setField(int64_t tag, const char* value, size_t len) override;
      virtual void setField(int64_t tag, int64_t value) override;
      virtual void setField(int64_t tag, double value) override;
      virtual void getField(int64_t tag, roe::StringOps::String_t& value) override;

    public:
      void dump(std::ostream& ostrm) const;

    public:
      std::unordered_map<int64_t, std::string> data_;
    };
  }
}
