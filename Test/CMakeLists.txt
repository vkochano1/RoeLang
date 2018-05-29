
file(GLOB TEST_CPP "*.cpp")

add_executable(Test ${TEST_CPP})
set (OTHER_LIBS pthread ${Boost_LIBRARIES} dl z)

if (BUILD_STATIC)

  if (EMBED_LLVM_LIBS)
    link_directories(${REPO_ROOT}/RoeLangLib)
    add_dependencies(Test EmbededRoeLang)
    target_link_libraries(Test ${OTHER_LIBS} RoeLangEmb  )
  elseif()
    link_directories(${REPO_ROOT}/RoeLangLib)
    add_dependencies(Test RoeLangStatic)
    target_link_libraries(Test ${OTHER_LIBS} RoeLangStatic)
  endif()

else()

  if (BUILD_DYNAMIC)
      link_directories(${REPO_ROOT}/RoeLangLib)
      add_dependencies(Test RoeLangDynamic)
      target_link_libraries(Test RoeLangDynamic ${OTHER_LIBS})
  endif()

endif()

add_custom_target(RUN_TEST ALL
  COMMAND ${REPO_ROOT}/Test/Test Test1.roe * VERBATIM
  COMMAND ${REPO_ROOT}/Test/Test Test2.roe * VERBATIM
  COMMAND ${CMAKE_COMMAND} -E echo "The below rules must fail"
  COMMAND ${REPO_ROOT}/Test/Test MustFail1.roe * -1 VERBATIM
  COMMAND ${REPO_ROOT}/Test/Test MustFail2.roe * -1 VERBATIM
  COMMAND ${REPO_ROOT}/Test/Test MustFail3.roe * -1 VERBATIM
  COMMAND ${REPO_ROOT}/Test/Test MustFail4.roe * -1 VERBATIM
  DEPENDS ${REPO_ROOT}/Test/Test
)
