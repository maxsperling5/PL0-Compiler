cmake_minimum_required (VERSION 3.5)
project (PL0-Compiler)

file (GLOB SRC app/Main.cpp
    src/pl0compiler/common/*.cpp
    src/pl0compiler/common/*.hpp
    src/pl0compiler/compiler/*.cpp
    src/pl0compiler/compiler/*.hpp)

add_executable (${PROJECT_NAME} ${SRC})