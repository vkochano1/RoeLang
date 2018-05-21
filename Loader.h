#pragma once

#include <Module/Module.h>
#include <unordered_map>

namespace roe
{
  class Loader final
  {
  public:
    using Modules = std::unordered_map<std::string, ModulePtr>;

  public:
    Loader();

  public:
    ModulePtr tryLoadModule(const std::string& name, const std::string& text);
    ModulePtr tryLoadModuleFromFile(const std::string& name, const std::string& path);
    void buildAll();
    void dumpAll(std::ostream&);
    Module::CompiledFunctionInfo getCompiledFunction(const std::string& moduleName, std::string& functionName);

  private:
    ModulePtr tryLoadModule_(const std::string& name, const std::istream& in);

  private:
    Modules modules_;
  };

}
