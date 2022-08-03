cmake_minimum_required(VERSION 3.9)

project(RoeLang)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -s -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s -O2 -Wall")

option(GENERATE_PARSER "Generate Parser and Scanner source code" OFF)
message("GENERATE_PARSER is ${GENERATE_PARSER}")

set (ROE_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

if(NOT LLVM_ROOT)
	set (LLVM_ROOT /usr/local/)
endif()

set (LLVM_INCLUDE_DIR  ${LLVM_ROOT}/include/)
set (LLVM_LIB_DIR  ${LLVM_ROOT}/lib/)


set (LLVM_LIB_NAMES tinfo LLVMLTO LLVMPasses LLVMMCJIT  LLVMObjCARCOpts LLVMSymbolize LLVMDebugInfoPDB LLVMDebugInfoDWARF LLVMFuzzMutate LLVMTableGen LLVMDlltoolDriver LLVMLineEditor LLVMOrcJIT LLVMCoverage LLVMMIRParser LLVMBPFDisassembler LLVMBPFCodeGen LLVMBPFAsmParser LLVMBPFDesc LLVMBPFInfo LLVMBPFAsmPrinter LLVMObjectYAML LLVMLibDriver LLVMOption LLVMWindowsManifest LLVMX86Disassembler LLVMX86AsmParser LLVMX86CodeGen LLVMGlobalISel LLVMSelectionDAG LLVMAsmPrinter LLVMX86Desc LLVMMCDisassembler LLVMX86Info LLVMX86AsmPrinter LLVMX86Utils  LLVMInterpreter LLVMExecutionEngine LLVMRuntimeDyld LLVMCodeGen LLVMTarget LLVMCoroutines LLVMipo LLVMInstrumentation LLVMVectorize LLVMScalarOpts LLVMLinker LLVMIRReader LLVMAsmParser LLVMInstCombine LLVMBitWriter LLVMAggressiveInstCombine LLVMTransformUtils LLVMAnalysis LLVMProfileData LLVMObject LLVMMCParser LLVMMC LLVMDebugInfoCodeView LLVMDebugInfoMSF LLVMBitReader LLVMCore LLVMBinaryFormat LLVMSupport LLVMDemangle)


######################## FLEX & BISON ###########################

if (GENERATE_PARSER)
  add_custom_target( Generators ALL
                    COMMAND cmake -E echo "Generating parsers..."
                    COMMAND flex -o Lexer/Scanner.cpp Lexer/Scanner.ll
                    COMMAND bison --defines=${ROE_ROOT}/Parser/Parser.hh -o ${ROE_ROOT}/Parser/Parser.cpp ${ROE_ROOT}/Parser/Parser.yy
                    DEPENDS ${ROE_ROOT}/Lexer/Scanner.ll ${ROE_ROOT}/Parser/Parser.yy
                    )
endif()


######################### Targets ################################
add_subdirectory(RoeLangLib)
add_subdirectory(Test)
