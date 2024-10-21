cmake_minimum_required(VERSION 3.15)

project(SMT VERSION 0.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic-errors")

set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(EXTERN_DIR "${PROJECT_SOURCE_DIR}/external")
set(BUILD_DIR "${PROJECT_SOURCE_DIR}/build")

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
endif()

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    add_subdirectory(tests)
endif()

add_subdirectory("${EXTERN_DIR}/cpp_cli")

set(SOURCES
  ${SRC_DIR}/SMTFile/SMTFile.cpp
  ${SRC_DIR}/Lexer/Token.cpp
  ${SRC_DIR}/Lexer/Lexer.cpp
  ${SRC_DIR}/AST/AST.cpp
  ${SRC_DIR}/SMTEvaluation/Evaluation.cpp
)

add_executable(evaluator main.cpp ${SOURCES})

target_link_libraries(evaluator PUBLIC cpp_cli)
target_include_directories(evaluator PUBLIC src/)


add_executable(generator generator.cpp)
