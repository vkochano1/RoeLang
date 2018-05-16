cmake_minimum_required(VERSION 3.9)

project(RoeLang)

set (REPO_ROOT /home/vkochano/RoeLang/RoeLang)

execute_process(COMMAND flex -o Lexer/Scanner.cpp Lexer/Scanner.ll)
execute_process(COMMAND bison --defines=${REPO_ROOT}/Parser/Parser.hh -o ${REPO_ROOT}/Parser/Parser.cpp ${REPO_ROOT}/Parser/Parser.yy)
execute_process(COMMAND  cd ${REPO_ROOT} && clang-format -i  ${REPO_ROOT}/Module/*)
execute_process(COMMAND  cd ${REPO_ROOT} && clang-format -i  ${REPO_ROOT}/AST/*)
execute_process(COMMAND  cd ${REPO_ROOT} && clang-format -i  ${REPO_ROOT}/Types/*)
execute_process(COMMAND  cd ${REPO_ROOT} &&  clang-format -i  ${REPO_ROOT}/Functions/*)
execute_process(COMMAND  cd ${REPO_ROOT} && clang-format -i ${REPO_ROOT}/Test/*)


set(CMAKE_CXX_STANDARD 14)

find_package(Boost)

include_directories(/usr/local/include ${Boost_INCLUDE_DIRS} ./ )


set(CMAKE_CXX_FLAGS "-O0 -s ")
#set(CMAKE_CXX_FLAGS "-O0 -g ")
file(GLOB AST_CPP "AST/*.cpp")
file(GLOB TYPES_CPP "Types/*.cpp")
file(GLOB MODULE_CPP "Module/*.cpp")
file(GLOB FUNCTIONS_CPP "Functions/*.cpp")
file(GLOB LEXER_CPP "Lexer/*.cpp")
file(GLOB PARSER_CPP "Parser/*.cpp")

add_library(RoeLang STATIC
${AST_CPP}
${TYPES_CPP}
${LEXER_CPP}
${PARSER_CPP}
${MODULE_CPP}
${FUNCTIONS_CPP}
Loader.cpp
)

add_executable(Test1  Test/Test.cpp)

target_link_libraries(Test1 RoeLang  pthread ${Boost_LIBRARIES} LLVMPasses LLVMipo LLVMInstrumentation LLVMVectorize LLVMLinker
LLVMX86Disassembler  LLVMX86AsmParser  LLVMX86CodeGen  LLVMGlobalISel  LLVMSelectionDAG  LLVMAsmPrinter  LLVMDebugInfoCodeView  LLVMDebugInfoMSF  LLVMCodeGen  LLVMScalarOpts  LLVMInstCombine  LLVMAggressiveInstCombine  LLVMTransformUtils  LLVMBitWriter  LLVMX86Desc  LLVMMCDisassembler  LLVMX86Info  LLVMX86AsmPrinter  LLVMX86Utils  LLVMMCJIT  LLVMExecutionEngine  LLVMTarget  LLVMAnalysis  LLVMProfileData  LLVMRuntimeDyld  LLVMObject  LLVMMCParser  LLVMBitReader  LLVMMC  LLVMCore  LLVMBinaryFormat  LLVMSupport  LLVMDemangle
dl z)
