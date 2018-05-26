
set(CMAKE_CXX_FLAGS "-O0 -s ")

file(GLOB AST_CPP "${REPO_ROOT}/AST/*.cpp")
file(GLOB TYPES_CPP "${REPO_ROOT}/Types/*.cpp")
file(GLOB MODULE_CPP "${REPO_ROOT}/Module/*.cpp")
file(GLOB FUNCTIONS_CPP "${REPO_ROOT}/Functions/*.cpp")
file(GLOB LEXER_CPP "${REPO_ROOT}/Lexer/*.cpp")
file(GLOB PARSER_CPP "${REPO_ROOT}/Parser/*.cpp")

add_library(RoeLang STATIC
${AST_CPP}
${TYPES_CPP}
${LEXER_CPP}
${PARSER_CPP}
${MODULE_CPP}
${FUNCTIONS_CPP}
Loader.cpp
)

target_link_libraries(RoeLang LLVMPasses LLVMipo LLVMInstrumentation LLVMVectorize LLVMLinker
LLVMX86Disassembler  LLVMX86AsmParser  LLVMX86CodeGen  LLVMGlobalISel  LLVMSelectionDAG  LLVMAsmPrinter  LLVMDebugInfoCodeView  LLVMDebugInfoMSF  LLVMCodeGen  LLVMScalarOpts  LLVMInstCombine  LLVMAggressiveInstCombine  LLVMTransformUtils  LLVMBitWriter  LLVMX86Desc  LLVMMCDisassembler  LLVMX86Info  LLVMX86AsmPrinter  LLVMX86Utils  LLVMMCJIT  LLVMExecutionEngine  LLVMTarget  LLVMAnalysis  LLVMProfileData  LLVMRuntimeDyld  LLVMObject  LLVMMCParser  LLVMBitReader  LLVMMC  LLVMCore  LLVMBinaryFormat  LLVMSupport  LLVMDemangle dl z)
