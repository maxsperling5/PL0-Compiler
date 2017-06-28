cmake_minimum_required (VERSION 3.5)
project (PL0-VM)

set (VM_SRC
    Code/vm.c
    Code/code.h
    Code/debug.h)

add_executable (${PROJECT_NAME} ${VM_SRC})