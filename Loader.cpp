#include <Loader.h>
#include <iterator>
#include <fstream>

namespace roe
{

  std::shared_ptr<Module> Loader::tryLoadModule(const std::string& name, const std::string& text)
  {
      auto module = std::make_shared<roe::Module> (name);
      if(!module->constructAST(text))
      {
        std::ostringstream ostrm;
        ostrm << "Failed to build AST from source" << module->errorText();
        throw std::runtime_error(ostrm.str());
      }

      /*std::initializer_list<std::shared_ptr<roe::IContainerAccess>> accessList = {
        access1, access2, access1};
      //m.bindFunctionParameterConstrains(functionToCall, accessList);
      */

      try
      {
        module->compileToIR();
      }
      catch(std::exception& ex)
      {
        std::ostringstream ostrm;
        ostrm << "Failed to generate IR code from AST" << ex.what();
        throw std::runtime_error(ostrm.str());
      }

      module->dumpIR();
      module->buildNative();

      modules_ [name] = module;
      return module;
  }

ModulePtr Loader::tryLoadModuleFromFile(const std::string& name, const std::string& path)
{
   std::ifstream in(path.c_str());

   std::istream_iterator<char> begin(in);
   std::istream_iterator<char> end;

   std::string text;
   text.reserve(4096);

   std::copy(begin, end, std::back_inserter(text));

   return tryLoadModule(name, text);
}

  Module::CompiledFunctionInfo Loader::getCompiledFunction(const std::string& moduleName, std::string& functionName)
  {
    auto fit = modules_.find(moduleName);

    if(fit == modules_.end())
      throw std::runtime_error ("Module not found");

    return fit->second->getFunc(functionName);
  }

}
