

file(GLOB AST_CPP       "${ROE_ROOT}/AST/*.cpp")
file(GLOB TYPES_CPP     "${ROE_ROOT}/Types/*.cpp")
file(GLOB MODULE_CPP    "${ROE_ROOT}/Module/*.cpp")
file(GLOB FUNCTIONS_CPP "${ROE_ROOT}/Functions/*.cpp")
file(GLOB LEXER_CPP     "${ROE_ROOT}/Lexer/*.cpp")
file(GLOB PARSER_CPP    "${ROE_ROOT}/Parser/*.cpp")

set (ROE_LANG_LIB_SRC ${AST_CPP} ${TYPES_CPP} ${LEXER_CPP} ${PARSER_CPP} ${MODULE_CPP} ${FUNCTIONS_CPP} Loader.cpp)

################################### Static lib #########################################
add_library(RoeLangStatic STATIC ${ROE_LANG_LIB_SRC})
target_include_directories(RoeLangStatic PUBLIC ${LLVM_INCLUDE_DIR} ${ROE_ROOT} ${ROE_ROOT}/Lexer)

######################### Static lib with dependencies ##################################

add_custom_target( EmbededRoeLang
                   COMMAND cmake -E echo "Embeding LLVM dependencies..."
                   COMMAND ${ROE_ROOT}/RoeLangLib/combine.sh ${LLVM_LIB_DIR} ${ROE_ROOT}/RoeLangLib/libRoeLangEmb.a
                   DEPENDS ${ROE_ROOT}/RoeLangLib/libRoeLangStatic.a
                 )

add_dependencies(EmbededRoeLang RoeLangStatic)

################################### Dynamic libs #########################################

add_library(RoeLangDynamic SHARED ${ROE_LANG_LIB_SRC} )

message("Using LLVM include dir: " ${LLVM_INCLUDE_DIR} )
message("Using LLVM lib dir: "     ${LLVM_LIB_DIR} )

target_include_directories(RoeLangDynamic PUBLIC ${LLVM_INCLUDE_DIR} ${ROE_ROOT} ${ROE_ROOT}/Lexer)
target_link_libraries(RoeLangDynamic ${LLVM_LIB_NAMES})
target_link_directories(RoeLangDynamic PUBLIC $${LLVM_LIB_DIR})


################################### Installation #########################################

install(TARGETS RoeLangDynamic LIBRARY DESTINATION lib)
install(TARGETS RoeLangStatic  ARCHIVE DESTINATION lib)

#install(FILES ${ROE_ROOT}/RoeLangLib/libRoeLangEmb.a DESTINATION lib)
install(DIRECTORY ../Types DESTINATION include/  FILES_MATCHING PATTERN "*.h")
install(DIRECTORY ../Module DESTINATION include/  FILES_MATCHING PATTERN "*.h")
install(DIRECTORY ../Functions DESTINATION include/  FILES_MATCHING PATTERN "*.h")
install(DIRECTORY ../RoeLangLib DESTINATION include/  FILES_MATCHING PATTERN "*.h")
