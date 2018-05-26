cmake_minimum_required(VERSION 3.9)

project(RoeLang)

set (REPO_ROOT /home/vkochano/RoeLang/RoeLang)

execute_process(COMMAND flex -o Lexer/Scanner.cpp Lexer/Scanner.ll)
execute_process(COMMAND bison --defines=${REPO_ROOT}/Parser/Parser.hh -o ${REPO_ROOT}/Parser/Parser.cpp ${REPO_ROOT}/Parser/Parser.yy)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost)
include_directories(/usr/local/include ${Boost_INCLUDE_DIRS} ./ )



add_subdirectory(RoeLangLib)
add_subdirectory(Test)
