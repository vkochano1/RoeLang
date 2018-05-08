#include <AST/ASTRules.h>

namespace roe
{



void ASTRules::addRule(ASTRulePtr rule)
{
    rules_[rule->name()] = rule;
}


    void ASTRules::evaluate()
    {
            size_t idx = 0;
            // insert declarations

            for (auto& rule : rules_)
            {
                     auto& context = rule.second->context();

                     //VK
                     auto* proto = llvm::FunctionType::get
                     (
                       context.types().voidType()
                     , {context.types().voidPtrType(), context.types().voidPtrType()}
                     , false
                    );

                    llvm::Function *f = llvm::cast<llvm::Function>(context.module()->getOrInsertFunction(rule.first, proto));
            }

            for (auto& rule : rules_)
            {
                rule.second->context().setCurrentRule(rule.first);
                rule.second->evaluate();
                ++idx;
            }
    }

}
