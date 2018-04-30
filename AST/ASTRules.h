#pragma once

#include <AST/ASTRule.h>
#include <unordered_map>

namespace roe
{

    class ASTRules
    {
    public:
        using RuleContainer = std::unordered_map<std::string, ASTRulePtr>; 
        
        void addRule(ASTRulePtr rule)
        {
            rules_[rule->name()] = rule; 
        }
        
        void evaluate()
        {
            size_t idx = 0;
            // insert declarations
            
            for (auto& rule : rules_)
            {
                     auto* proto = llvm::FunctionType::get
                     (
                       Types::instance().longType()
                     , {Types::instance().voidPtrType(), Types::instance().voidPtrType()}
                     , false
                    );
       
                    llvm::Function *f = llvm::cast<llvm::Function>(rule.second->context().module()->getOrInsertFunction(rule.first, proto));
            }
            
            for (auto& rule : rules_)
            {
                rule.second->context().setCurrentRule(rule.first);
                rule.second->evaluate();
                ++idx;
            }
        }
        
    private:
        RuleContainer rules_;
    };
    
}
