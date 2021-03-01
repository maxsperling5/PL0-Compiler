cmake_minimum_required (VERSION 3.5)
project (PL0-Compiler)

file (GLOB SRC app/Main.cpp
    src/pl0compiler/logger/Logger.cpp
    src/pl0compiler/logger/Logger.hpp
    src/pl0compiler/fileio/FileIO.cpp
    src/pl0compiler/fileio/FileIO.hpp
    src/pl0compiler/compiler/*.cpp
    src/pl0compiler/compiler/*.hpp)

add_executable (${PROJECT_NAME} ${SRC})