
#include <RoeLangLib/Loader.h>
#include <Test/DummyContainer.h>
#include <chrono>
#include <fstream>
#include <iostream>

int main(int argc, char* argv[])
{
  if (argc != 3)
    std::exit(0);

  std::string moduleFile     = argv[1];
  std::string functionToCall = argv[2];

  try
  {
    std::shared_ptr<roe::IConstraints> constraints(new roe::test::DummyConstraints());
    roe::test::DummyContainer          container1, container2, container3;
    roe::Loader                        loader;

    auto modulePtr = loader.tryLoadModuleFromFile(moduleFile, moduleFile);
    modulePtr->bindParamsConstraints(functionToCall, {constraints, constraints, constraints});
    modulePtr->compileToIR();
    loader.buildAll();

    auto compiledFunction = loader.getCompiledFunction(moduleFile, functionToCall);
    compiledFunction.call(&container1, &container2, &container3);
  }
  catch (std::exception& exp)
  {
    std::cerr << exp.what() << std::endl;
    return -1;
  }

  return 0;
}
