
#include <RoeLangLib/Loader.h>
#include <Test/DummyContainer.h>
#include <chrono>
#include <fstream>
#include <iostream>

int main(int argc, char* argv[])
{
  if (argc < 3)
  {
    std::cerr << "Usage: " << argv[0] << " <MODULE NAME> <FUNCTION NAME> [EXPECTED_RETURN_CODE=0]";
    return -1;
  }

  size_t expectedReturnCode = 0;
  if(argc == 4)
  {
    char* ptrEnd = nullptr;
    expectedReturnCode = std::strtol(argv[3],&ptrEnd, 10);
  }

  std::string moduleFile     = argv[1];
  std::string functionToCall = argv[2];

  try
  {
    std::shared_ptr<roe::IConstraints> constraints(new roe::test::DummyConstraints());

    roe::Loader                        loader;

    auto modulePtr = loader.tryLoadModuleFromFile(moduleFile, moduleFile);

    if (functionToCall != "*")
    {
      roe::test::DummyContainer          container1, container2, container3;
      modulePtr->bindParamsConstraints(functionToCall, {constraints, constraints, constraints});
      modulePtr->compileToIR();
      loader.buildAll();

      auto compiledFunction = loader.getCompiledFunction(moduleFile, functionToCall);
      compiledFunction.call(&container1, &container2, &container3);
    }
    else
    {
      for (auto& compiledFunction : modulePtr->context().rules())
      {
          modulePtr->bindParamsConstraints(compiledFunction.first, {constraints, constraints, constraints});
      }

      modulePtr->compileToIR();
      //modulePtr->dumpIR(std::cout);
      loader.buildAll();

      for (auto& compiledFunction : modulePtr->functions())
      {
        std::cout <<"Executing " << moduleFile << ":" << compiledFunction.first << std::endl;
        roe::test::DummyContainer          container1, container2, container3;
        compiledFunction.second.call(&container1, &container2, &container3);
      }
    }
  }
  catch (std::exception& exp)
  {
    std::cerr << exp.what() << std::endl;
    return !(-1 == expectedReturnCode);
  }

  return !(0 == expectedReturnCode);
}
