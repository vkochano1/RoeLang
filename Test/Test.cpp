// $Id$

#include <iostream>
#include <fstream>

#include <Driver.h>
#include <fstream>
#include <sstream>

#include "llvm/IR/Verifier.h"
#include "llvm/IR/Argument.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ExecutionEngine/GenericValue.h"


#include "llvm/Support/TargetSelect.h"
#include <llvm/ExecutionEngine/ExecutionEngine.h>

#include <llvm/ExecutionEngine/MCJIT.h>

#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"
#include <Types.h>
#include <Bindings.h>
#include <FunctionRegistrar.h>
#include <Module.h>


class ContainerAccess : public roe::IContainerAccess
{
public:
    virtual void  setField(int64_t tag, const roe::StringOps::String_t& value)
    {
     data_ [tag] = std::string(value.data, value.len_);
    }

    virtual void  setField(int64_t tag, const char* value, size_t len)
    {
     data_ [tag] = std::string(value, len);
    }

    virtual void  getField(int64_t tag, roe::StringOps::String_t& value)
    {
        std::string& val =  data_[tag];
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
        for ( const auto& p : data_)
        {
            ostrm << p.first <<  " -> " << p.second << std::endl;
        }
    }

    void setTagFromFieldNameMapping(roe::IContainerAccess::FieldNameToTagMapping&& mapping)
    {
      fieldNameToTagMapping_.swap(mapping);
    }

public:
    std::unordered_map<int64_t, std::string>  data_;
};


int main(int argc, char *argv[])
{
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmParser();
    llvm::InitializeNativeTargetAsmPrinter();

   std::ifstream in ("in.txt");
   std::string line;
   std::string tmp;
   while (!std::getline(in, tmp).eof())
   {
     line += tmp + '\n';
   }

    roe::Module m("newMod");

    roe::IContainerAccess::FieldNameToTagMapping mapping =
    {
        {"Symbol", 55}
      , {"Suffix", 65}
      , {"Side", 54}
      , {"OrdType", 40}
      , {"OrdQty", 38}
      , {"Account", 1}
      , {"LimitPrice", 44}
    };

    auto mapping2 = mapping;



    std::shared_ptr<roe::IContainerAccess> access1 (new ContainerAccess());

    ContainerAccess* paccess1 = (ContainerAccess*)access1.get();
    paccess1->setTagFromFieldNameMapping(std::move(mapping));

    std::shared_ptr<roe::IContainerAccess> access2 (new ContainerAccess());
    ContainerAccess* paccess2 = (ContainerAccess*)access2.get();
    paccess2->setTagFromFieldNameMapping(std::move(mapping2));

    m.constructAST(line);
    auto& r = m.context().rule("JOPA");
    r.bindParameter("A", access1);
    r.bindParameter("B", access2);

    m.compileToIR();
    m.dumpIR();
    m.buildNative();

    auto& f = m.getFunc("JOPA");


    try
    {
      f.call(access1.get(), access2.get());
    }
    catch(std::exception& ex)
    {
        std::cerr << ex.what();
    }

    paccess1->dump(std::cout);
    paccess2->dump(std::cout);
}
