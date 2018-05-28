
set(CMAKE_CXX_FLAGS "-O0 -s ")

file(GLOB AST_CPP       "${REPO_ROOT}/AST/*.cpp")
file(GLOB TYPES_CPP     "${REPO_ROOT}/Types/*.cpp")
file(GLOB MODULE_CPP    "${REPO_ROOT}/Module/*.cpp")
file(GLOB FUNCTIONS_CPP "${REPO_ROOT}/Functions/*.cpp")
file(GLOB LEXER_CPP     "${REPO_ROOT}/Lexer/*.cpp")
file(GLOB PARSER_CPP    "${REPO_ROOT}/Parser/*.cpp")

set (ROE_LANG_LIB_SRC
${AST_CPP}
${TYPES_CPP}
${LEXER_CPP}
${PARSER_CPP}
${MODULE_CPP}
${FUNCTIONS_CPP}
Loader.cpp)

if (BUILD_STATIC)

  add_library(RoeLangStatic STATIC ${ROE_LANG_LIB_SRC})

  if (EMBED_LLVM_LIBS)
    ###### Embedded RoeLangLib #################

    set(LLVM_ARCH_COMMAND_ARGS ${REPO_ROOT}/RoeLangLib/libRoeLang.a)

    foreach (LLVM_ARCH_LIB ${LLVM_LIBS_TO_ARCHIVE})
      list (APPEND LLVM_ARCH_COMMAND_ARGS  ${LLVM_ARCH_LIB})
    endforeach(LLVM_ARCH_LIB)

    add_custom_target( EmbededRoeLang ALL
                  COMMAND cmake -E echo "Embeding LLVM dependencies..."
                  COMMAND ar -rc libRoeLangEmb.a ${LLVM_ARCH_COMMAND_ARGS} VERBATIM
                  DEPENDS ${REPO_ROOT}/RoeLangLib/libRoeLang.a
                 )
    add_dependencies(EmbededRoeLang RoeLangStatic)
  endif()

endif()

if (BUILD_DYNAMIC)

  add_library(RoeLangDynamic SHARED ${ROE_LANG_LIB_SRC} )
  target_link_libraries(RoeLangDynamic ${LLVM_LIB_NAMES})
endif()
