cmake_minimum_required (VERSION 3.5)
project (PL0-Compiler)

file (GLOB COMP_SRC
    Code/Comp/PL0toCL0/*.hh
    Code/Comp/PL0toCL0/*.cc)

set (VIEW_SRC
    Code/View/CLI/ViewCLI.hh
    Code/View/CLI/ViewCLI.cc)

set (DATA_SRC
    Code/Data/File/DataFile.hh
    Code/Data/File/DataFile.cc)

set (MAIN_SRC
    Code/Main.cc
    Code/Comp/IComp.hh
    Code/View/IView.hh
    Code/Data/IData.hh)

add_library (Comp SHARED ${COMP_SRC})
add_library (View SHARED ${VIEW_SRC})
add_library (Data SHARED ${DATA_SRC})
add_executable (PL0-Compiler ${MAIN_SRC})
target_link_libraries (PL0-Compiler Comp View Data)