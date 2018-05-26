#!/bin/bash

DIRS=("AST" "Exceptions" "Lexer" "Parser" "Types" "Module" "Functions" "Test")

for DIR in ${DIRS[@]}; do
  echo "Formatting $DIR ..."
  clang-format -i ../$DIR/*.h
  clang-format -i ../$DIR/*.cpp
  clang-format -i ../$DIR/*.roe
done
