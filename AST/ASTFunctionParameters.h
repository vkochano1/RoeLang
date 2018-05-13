#pragma once

#include <memory>
#include <string>
#include <vector>

namespace roe
{
  class Context;

  class ASTFunctionParameters
  {
  public:
    using Parameters = std::vector<std::string>;

  public:
    ASTFunctionParameters(Context& context);

  public:
    void addParameter(const std::string& name);
    const Parameters& parameters() const;

  private:
    Parameters parameters_;
    Context&   context_;
  };

  using ASTFunctionParametersPtr = std::shared_ptr<ASTFunctionParameters>;
}
