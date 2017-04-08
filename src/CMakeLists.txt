cmake_minimum_required(VERSION 2.8)
add_executable(
  pig
  lexer.cpp
  main.cpp
  token.cpp
  token_stream.cpp)
include_directories(${PROJECT_SOURCE_DIR}/include)
