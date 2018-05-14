
#include <fstream>
#include <iostream>
#include <Loader.h>
#include <chrono>

class ContainerAccess : public roe::IContainerAccess
{
public:
  virtual void setField(int64_t tag, const roe::StringOps::String_t& value)
  {
    //data_[tag] = std::string(value.data, value.len_);
  }

  virtual void setField(int64_t tag, const char* value, size_t len)
  {
    //data_[tag] = std::string(value, len);
  }

  virtual void setField(int64_t tag, int64_t value)
  {
    //data_[tag] = std::to_string(value);
  }
  virtual void setField(int64_t tag, double value)
  {
    //data_[tag] = std::to_string(value);
  }
  virtual void getField(int64_t tag, roe::StringOps::String_t& value)
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

  void dump(std::ostream& ostrm) const
  {
    for (const auto& p : data_)
    {
      ostrm << p.first << " -> " << p.second << std::endl;
    }
  }

  void setTagFromFieldNameMapping(
    roe::IContainerAccess::FieldNameToTagMapping&& mapping)
  {
    fieldNameToTagMapping_.swap(mapping);
  }

public:
  std::unordered_map<int64_t, std::string> data_;
};

void test ()
{

  int local = 23;
  double d = 1.0 + 10/2;
  std::string s = std::string("123") + "XXX";
  std::string sub = s.substr(2,2);
  double d2 = 0 -  2/32.01 * (-1);
  if (1)
  {
    std::string sR = "dfdfdfdf";
  }
}

int main(int argc, char* argv[])
{

  if (argc != 4)
    std::exit(0);

  std::string   moduleFile     = argv[1];
  std::string   functionToCall = argv[2];
  char* ptrEnd = nullptr;
  size_t N    = strtol(argv[3], &ptrEnd, 10);

  llvm::InitializeNativeTarget();
  llvm::InitializeNativeTargetAsmParser();
  llvm::InitializeNativeTargetAsmPrinter();

  roe::IContainerAccess::FieldNameToTagMapping mapping = {
    {"Symbol", 55}, {"Suffix", 65}, {"Side", 54},      {"OrdType", 40},
    {"OrdQty", 38}, {"Account", 1}, {"LimitPrice", 44}};

  auto mapping2 = mapping;

  std::shared_ptr<roe::IContainerAccess> access1(new ContainerAccess());

  ContainerAccess* paccess1 = (ContainerAccess*)access1.get();
  paccess1->setTagFromFieldNameMapping(std::move(mapping));

  std::shared_ptr<roe::IContainerAccess> access2(new ContainerAccess());
  ContainerAccess* paccess2 = (ContainerAccess*)access2.get();
  paccess2->setTagFromFieldNameMapping(std::move(mapping2));

  try
  {
    roe::Loader loader;
    loader.tryLoadModuleFromFile(moduleFile, moduleFile);
    auto  f = loader.getCompiledFunction(moduleFile, functionToCall);

    auto start = std::chrono::high_resolution_clock::now();
    for(size_t i = 0 ; i < N; ++i)
    {
      f.call(access1.get(), access2.get(), access1.get());
    }

    auto end =  std::chrono::high_resolution_clock::now();

    auto res = std::chrono::duration_cast<std::chrono::nanoseconds> (end - start).count();
    std::cout << res / N  << std::endl;

    paccess1->dump(std::cout);
    paccess2->dump(std::cout);


    {
      auto start = std::chrono::high_resolution_clock::now();

      for(size_t i = 0 ; i < N; ++i)
        test();
      auto end =  std::chrono::high_resolution_clock::now();

      auto res = std::chrono::duration_cast<std::chrono::nanoseconds> (end - start).count();
      std::cout << res / N  << std::endl;
    }
  }
  catch (std::exception& exp)
  {
    std::cerr << exp.what() << std::endl;
  }
}
