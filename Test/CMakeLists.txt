set(CMAKE_CXX_FLAGS "-O0 -s ")

file(GLOB TEST_CPP "*.cpp")

add_executable(Test ${TEST_CPP})

target_link_libraries(Test dl z RoeLang  pthread ${Boost_LIBRARIES} dl z)
