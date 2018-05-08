#include <AST/ASTFunctionParameters.h>
#include <Module/Context.h>

namespace roe
{
    ASTFunctionParameters::ASTFunctionParameters(Context& context)
      : context_(context)
    {

    }

    void ASTFunctionParameters::addParameter(const std::string& name)
    {
        parameters_.push_back(name);
    }

    const ASTFunctionParameters::Parameters& ASTFunctionParameters::parameters() const
    {
        return parameters_;
    }
}
