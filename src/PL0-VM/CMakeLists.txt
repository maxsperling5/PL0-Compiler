cmake_minimum_required (VERSION 3.5)
project (PL0-VM)

set (VM_SRC
	vm.c
	code.h
	debug.h)

add_executable (PL0-VM ${VM_SRC})