#include <AST/ASTVariable.h>
#include <FunctionRegistrar.h>
#include <boost/algorithm/string.hpp>


namespace roe
{

    const std::string ASTVariable::TAG_PREFIX   = "tag";
    const std::string ASTVariable::FIELD_PREFIX = "field";
    
    ASTVariable::ASTVariable(Context& context, const std::string& var)
    : ASTElement(context)
    , tag_(-1)
    {
        processContainerField(var);
        var_= var;
    }
    
    bool ASTVariable::processContainerField(const std::string& fullVarName)
    {
        std::vector<std::string> varComponents;
        boost::split(varComponents, fullVarName, boost::is_any_of("."));
        
        if(2 != varComponents.size())
        {
            return false;
        }
        
        baseName_ = varComponents[0];
        const auto& fieldName = varComponents[1];
        
        isField_ = true;
        
        if (fieldName.find(TAG_PREFIX) == 0)
        {
            auto tagStr = fieldName.substr(TAG_PREFIX.length());
            char* endp = nullptr;
            tag_ = std::strtol(tagStr.c_str(),&endp,10);
            return true;
        }
        else if (fieldName.find(FIELD_PREFIX) == 0)
        {
            auto fieldStr = fieldName.substr(FIELD_PREFIX.length());
            tag_ = context_.getTagFromFieldName(fieldStr);
            return true;
        }
        
        return false;
        
    }
    
    size_t ASTVariable::tag() const
    {
        return tag_;
    }
    
    const std::string& ASTVariable::name () const 
    { 
        return var_;
    }
    
    const std::string& ASTVariable::baseName () const 
    { 
        return baseName_;
    }

    bool ASTVariable::isField () const 
    { 
        return isField_;
    }
    
    llvm::Value* ASTVariable::evaluateField()
    {
        auto& builder = context_.rule().builder();
        
        llvm::Value* result  = builder.CreateAlloca(Types::instance().stringType());
        llvm::Value* container = context_.rule().getParamValue(baseName());
        llvm::Value* tagVal = llvm::ConstantInt::get(Types::instance().longType(), tag());
        
        FunctionRegistrar::instance().makeCall(context_,"getField", {container, tagVal, result} );
        return result;
    }
    
    llvm::Value* ASTVariable::evaluateLocalVar()
    {
        auto& info = context_.getVariable(var_);
        llvm::Value* result = info.value();
        return  result;
    }
    
    llvm::Value* ASTVariable::evaluate()
    {
         if(isField())
         {
            return evaluateField();
         }
         
         return evaluateLocalVar();        
    }

}
