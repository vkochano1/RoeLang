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



void writeModuleToFile(llvm::Module *module)
{
    using namespace llvm;
	std::string std_file_stream;
	raw_string_ostream file_stream(std_file_stream);
	module->print(file_stream, nullptr);
    std::cout << file_stream.str();
}

int main(int argc, char *argv[])
{
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmParser();
    llvm::InitializeNativeTargetAsmPrinter();
        
    
    
   // std::cout << "Reading expressions from in.txt" << std::endl;

   std::ifstream in ("in.txt");
   std::string line;
   std::string tmp;
   while (!std::getline(in, tmp).eof())
   {
    line += tmp + '\n';
   }
    
    roe::Module m("newMod");
    roe::Context::FieldNameToTagMapping mapping = { {"Symbol", 55}, {"Suffix", 65}, {"Side", 54}, {"OrdType", 40}, {"OrdQty", 38}, {"Account", 1}, {"LimitPrice", 44} };
    m.context().setTagFromFieldNameMapping(std::move(mapping));
    m.compileToIR(line);
    m.dumpIR();
    m.buildNative();
    auto& f = m.getFunc("JOPA");
    
    roe::ContainerAccess access1;
    roe::ContainerAccess access2;
    f.call(&access1, &access2);
    
    access1.dump(std::cout);
    access2.dump(std::cout);
}
