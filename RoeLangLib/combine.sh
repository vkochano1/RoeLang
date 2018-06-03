#!/bin/bash

LLVM_LIB_DIR=$1
OUT_ARCH=$2
ar -M << -end
create OUT_ARCH
addlib libRoeLangStatic.a
addlib $LLVM_LIB_DIR/libLLVMPasses.a
addlib $LLVM_LIB_DIR/libLLVMipo.a
addlib $LLVM_LIB_DIR/libLLVMInstrumentation.a
addlib $LLVM_LIB_DIR/libLLVMVectorize.a
addlib $LLVM_LIB_DIR/libLLVMX86Disassembler.a
addlib $LLVM_LIB_DIR/libLLVMX86AsmParser.a
addlib $LLVM_LIB_DIR/libLLVMX86CodeGen.a
addlib $LLVM_LIB_DIR/libLLVMGlobalISel.a
addlib $LLVM_LIB_DIR/libLLVMSelectionDAG.a
addlib $LLVM_LIB_DIR/libLLVMAsmPrinter.a
addlib $LLVM_LIB_DIR/libLLVMDebugInfoCodeView.a
addlib $LLVM_LIB_DIR/libLLVMDebugInfoMSF.a
addlib $LLVM_LIB_DIR/libLLVMCodeGen.a
addlib $LLVM_LIB_DIR/libLLVMScalarOpts.a
addlib $LLVM_LIB_DIR/libLLVMInstCombine.a
addlib $LLVM_LIB_DIR/libLLVMAggressiveInstCombine.a
addlib $LLVM_LIB_DIR/libLLVMTransformUtils.a
addlib $LLVM_LIB_DIR/libLLVMBitWriter.a
addlib $LLVM_LIB_DIR/libLLVMX86Desc.a
addlib $LLVM_LIB_DIR/libLLVMMCDisassembler.a
addlib $LLVM_LIB_DIR/libLLVMX86Info.a
addlib $LLVM_LIB_DIR/libLLVMX86AsmPrinter.a
addlib $LLVM_LIB_DIR/libLLVMX86Utils.a
addlib $LLVM_LIB_DIR/libLLVMMCJIT.a
addlib $LLVM_LIB_DIR/libLLVMExecutionEngine.a
addlib $LLVM_LIB_DIR/libLLVMTarget.a
addlib $LLVM_LIB_DIR/libLLVMAnalysis.a
addlib $LLVM_LIB_DIR/libLLVMProfileData.a
addlib $LLVM_LIB_DIR/libLLVMRuntimeDyld.a
addlib $LLVM_LIB_DIR/libLLVMObject.a
addlib $LLVM_LIB_DIR/libLLVMMCParser.a
addlib $LLVM_LIB_DIR/libLLVMBitReader.a
addlib $LLVM_LIB_DIR/libLLVMMC.a
addlib $LLVM_LIB_DIR/libLLVMCore.a
addlib $LLVM_LIB_DIR/libLLVMBinaryFormat.a
addlib $LLVM_LIB_DIR/libLLVMSupport.a
addlib $LLVM_LIB_DIR/libLLVMDemangle.a
save
end
-end
