cmake_minimum_required (VERSION 3.5)
project (PL0-Compiler)

file (GLOB COMP_SRC
    Code/Comp/CompPL0/*.hh
    Code/Comp/CompPL0/*.cc)

set (VIEW_SRC
    Code/View/ViewCLI/ViewCLI.hh
    Code/View/ViewCLI/ViewCLI.cc)

set (DATA_SRC
    Code/Data/DataFile/DataFile.hh
    Code/Data/DataFile/DataFile.cc)

set (MAIN_SRC
    Code/Main.cc
    Code/Comp/IComp.hh
    Code/View/IView.hh
    Code/Data/IData.hh)

add_library (Comp SHARED ${COMP_SRC})
add_library (View SHARED ${VIEW_SRC})
add_library (Data SHARED ${DATA_SRC})
add_executable (${PROJECT_NAME} ${MAIN_SRC})
target_link_libraries (${PROJECT_NAME} Comp View Data)