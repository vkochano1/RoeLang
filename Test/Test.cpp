
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

public:
  std::unordered_map<int64_t, std::string> data_;
};


int main(int argc, char* argv[])
{

  if (argc != 3)
    std::exit(0);

  std::string   moduleFile     = argv[1];
  std::string   functionToCall = argv[2];

  llvm::InitializeNativeTarget();
  llvm::InitializeNativeTargetAsmParser();
  llvm::InitializeNativeTargetAsmPrinter();

  /*roe::IContainerAccess::FieldNameToTagMapping mapping = {
    {"Symbol", 55}, {"Suffix", 65}, {"Side", 54},      {"OrdType", 40},
    {"OrdQty", 38}, {"Account", 1}, {"LimitPrice", 44}};

  auto mapping2 = mapping;

  //std::shared_ptr<roe::IContainerAccess> access1(new ContainerAccess());

  //ContainerAccess* paccess1 = (ContainerAccess*)access1.get();
  //paccess1->setTagFromFieldNameMapping(std::move(mapping));

  //std::shared_ptr<roe::IContainerAccess> access2(new ContainerAccess());
  //ContainerAccess* paccess2 = (ContainerAccess*)access2.get();
  //paccess2->setTagFromFieldNameMapping(std::move(mapping2));

  //std::initializer_list<std::shared_ptr<roe::IContainerAccess>> accessList = {
  //  access1, access2, access1};
  //m.bindFunctionParameterConstrains(functionToCall, accessList);
  */

  try
  {
    ContainerAccess container1, container2, container3;
    roe::Loader loader;
    auto modulePtr = loader.tryLoadModuleFromFile(moduleFile, moduleFile);
    ///modulePtr->bindFunctionParameterConstrains(functionToCall, accessList);
    modulePtr->compileToIR();
    loader.buildAll();
    auto  f  = loader.getCompiledFunction(moduleFile, functionToCall);
    f.call(&container1, &container2, &container3);
  }
  catch (std::exception& exp)
  {
    std::cerr << exp.what() << std::endl;
    return -1;
  }

  return 0;
}
