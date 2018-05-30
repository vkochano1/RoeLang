cmake_minimum_required(VERSION 3.9)

project(RoeLang)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-O0 -s ")

option(EMBED_LLVM_LIBS "Embed all llvm libs into libRoeLang.a" OFF)
message("EMBED_LLVM_LIBS is ${EMBED_LLVM_LIBS}")

option(BUILD_STATIC " Build libRoeLang.a"  OFF)
message("BUILD_STATIC is ${BUILD_STATIC}")

option(BUILD_DYNAMIC "Build libRoeLang.so" ON)
message("BUILD_DYNAMIC is ${BUILD_DYNAMIC}")

option(BUILD_TESTS   "Build Test"          ON)
message("BUILD_TESTS is ${BUILD_TESTS}")

option(GENERATE_PARSER "Generate Parser and Scanner source code" OFF)
message("GENERATE_PARSER is ${GENERATE_PARSER}")

if (NOT DEFINED REPO_ROOT)
  set (REPO_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
endif()

#################### LLVM setup  #######################

if (NOT DEFINED LLVM_INCLUDE_DIR)
  set (LLVM_INCLUDE_DIR /usr/local/include/)
endif()

if (NOT DEFINED LLVM_LIB_DIR)
  set (LLVM_LIB_DIR /usr/local/lib/)
endif()

set (LLVM_LIB_NAMES
LLVMPasses LLVMipo LLVMInstrumentation
LLVMVectorize LLVMLinker LLVMX86Disassembler
LLVMX86AsmParser  LLVMX86CodeGen  LLVMGlobalISel
LLVMSelectionDAG  LLVMAsmPrinter  LLVMDebugInfoCodeView
LLVMDebugInfoMSF  LLVMCodeGen  LLVMScalarOpts
LLVMInstCombine LLVMAggressiveInstCombine
LLVMTransformUtils  LLVMBitWriter  LLVMX86Desc
LLVMMCDisassembler  LLVMX86Info  LLVMX86AsmPrinter
LLVMX86Utils  LLVMMCJIT  LLVMExecutionEngine
LLVMTarget  LLVMAnalysis  LLVMProfileData
LLVMRuntimeDyld  LLVMObject  LLVMMCParser
LLVMBitReader  LLVMMC  LLVMCore
LLVMBinaryFormat  LLVMSupport  LLVMDemangle
)

set (LLVM_LIBS_TO_ARCHIVE "")

foreach (LLVM_LIB ${LLVM_LIB_NAMES})
  LIST(APPEND LLVM_LIBS_TO_ARCHIVE "${LLVM_LIB_DIR}/lib${LLVM_LIB}.a")
endforeach(LLVM_LIB)


######################## FLEX & BISON ###########################

if (GENERATE_PARSER)
  add_custom_target( Generators ALL
                    COMMAND cmake -E echo "Generating parsers..."
                    COMMAND flex -o Lexer/Scanner.cpp Lexer/Scanner.ll
                    COMMAND bison --defines=${REPO_ROOT}/Parser/Parser.hh -o ${REPO_ROOT}/Parser/Parser.cpp ${REPO_ROOT}/Parser/Parser.yy
                    DEPENDS ${REPO_ROOT}/Lexer/Scanner.ll ${REPO_ROOT}/Parser/Parser.yy
                    )
endif()

######################### Common settings #######################

include_directories(
${LLVM_INCLUDE_DIR}
${REPO_ROOT}
${REPO_ROOT}/RoeLangLib
${REPO_ROOT}/Lexer)

######################### Targets #######################

add_subdirectory(RoeLangLib)

if(BUILD_TESTS)
  add_subdirectory(Test)
endif()
