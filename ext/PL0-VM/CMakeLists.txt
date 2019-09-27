cmake_minimum_required (VERSION 3.5)
project (PL0-VM)

set (SRC
    src/vm.c
    src/code.h
    src/debug.h)

add_executable (${PROJECT_NAME} ${SRC})