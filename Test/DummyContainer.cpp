#include <Test/DummyContainer.h>

namespace roe
{
  namespace test
  {

    DummyConstraints::DummyConstraints()
    {
      fieldNameToTagMapping_ = {{"Symbol", 55},   {"Suffix", 65}, {"Side", 54},      {"OrdType", 40},
                                {"OrderQty", 38}, {"Account", 1}, {"LimitPrice", 44}};
    }

    void DummyContainer::setField(int64_t tag, const roe::StringOps::String_t& value)
    {
      data_[tag] = std::string(value.data, value.len_);
    }

    void DummyContainer::setField(int64_t tag, const char* value, size_t len)
    {
      data_[tag] = std::string(value, len);
    }

    void DummyContainer::setField(int64_t tag, int64_t value)
    {
      data_[tag] = std::to_string(value);
    }

    void DummyContainer::setField(int64_t tag, double value)
    {
      data_[tag] = std::to_string(value);
    }
    void DummyContainer::getField(int64_t tag, roe::StringOps::String_t& value)
    {
      std::string& val = data_[tag];
      if (val.length() == 0)
      {
        value.len_ = 0;
        return;
      }
      std::strncpy(&value.data[0], &val[0], val.length());
      value.len_ = val.length();
    }

    void DummyContainer::dump(std::ostream& ostrm) const
    {
      for (const auto& p : data_)
      {
        ostrm << p.first << " -> " << p.second << std::endl;
      }
    }
  }
}
