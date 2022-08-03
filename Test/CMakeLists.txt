
file(GLOB TEST_CPP "*.cpp")
file(GLOB TEST_ROE "*.roe")

set (OTHER_LIBS pthread  dl z)

add_executable(Test ${TEST_CPP})
target_include_directories(Test PUBLIC  ${LLVM_INCLUDE_DIR} ${ROE_ROOT})
target_link_directories(Test PUBLIC ${ROE_ROOT}/RoeLangLib ${LLVM_LIB_DIR})
add_dependencies(Test RoeLangDynamic)


target_link_libraries(Test RoeLangDynamic ${OTHER_LIBS})

#add_custom_target(RUN_TEST ALL
#  COMMAND ${ROE_ROOT}/Test/Test Test1.roe * VERBATIM
#  COMMAND ${ROE_ROOT}/Test/Test Test2.roe * VERBATIM
#  COMMAND ${CMAKE_COMMAND} -E echo "The below rules must fail"
#  COMMAND ${ROE_ROOT}/Test/Test MustFail1.roe * -1 VERBATIM
#  COMMAND ${ROE_ROOT}/Test/Test MustFail2.roe * -1 VERBATIM
#  COMMAND ${ROE_ROOT}/Test/Test MustFail3.roe * -1 VERBATIM
#  COMMAND ${ROE_ROOT}/Test/Test MustFail4.roe * -1 VERBATIM
#  DEPENDS ${ROE_ROOT}/Test/Test
#)

################################### Installation #########################################

install(TARGETS Test DESTINATION bin)

install(FILES ${TEST_ROE} DESTINATION bin )
