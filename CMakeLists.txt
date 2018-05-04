cmake_minimum_required(VERSION 3.9)

project(RoeLang)

execute_process(COMMAND flex -o Lexer/Scanner.cpp Lexer/Scanner.ll)
execute_process(COMMAND bison --defines=Parser/Parser.hh -o Parser/Parser.cpp Parser/Parser.yy)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost)

include_directories(/usr/local/include ${Boost_INCLUDE_DIRS} ./ )


set(CMAKE_CXX_FLAGS "-O0 -s -DEXEC")
file(GLOB AST_CPP "AST/*.cpp")


add_library(RoeLangLib STATIC
StringOps.cpp 
Bindings.cpp 
${AST_CPP} 
Types.cpp 
Context.cpp  
Module.cpp
Parser/Parser.cpp 
Lexer/Scanner.cpp 
Driver.cpp)

add_executable(Test1  Test/Test.cpp)

target_link_libraries(Test1 RoeLangLib  pthread ${Boost_LIBRARIES} 
LLVMX86Disassembler  LLVMX86AsmParser  LLVMX86CodeGen  LLVMGlobalISel  LLVMSelectionDAG  LLVMAsmPrinter  LLVMDebugInfoCodeView  LLVMDebugInfoMSF  LLVMCodeGen  LLVMScalarOpts  LLVMInstCombine  LLVMAggressiveInstCombine  LLVMTransformUtils  LLVMBitWriter  LLVMX86Desc  LLVMMCDisassembler  LLVMX86Info  LLVMX86AsmPrinter  LLVMX86Utils  LLVMMCJIT  LLVMExecutionEngine  LLVMTarget  LLVMAnalysis  LLVMProfileData  LLVMRuntimeDyld  LLVMObject  LLVMMCParser  LLVMBitReader  LLVMMC  LLVMCore  LLVMBinaryFormat  LLVMSupport  LLVMDemangle
dl z)

