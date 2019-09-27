cmake_minimum_required (VERSION 3.5)
project (PL0-Compiler)

file (GLOB COMP_SRC
    src/comp/CompFactory.cpp
    src/comp/comp_pl0/*.hpp
    src/comp/comp_pl0/*.cpp)

set (VIEW_SRC
    src/view/ViewFactory.cpp
    src/view/view_cli/ViewCLI.hpp
    src/view/view_cli/ViewCLI.cpp)

set (DATA_SRC
    src/data/DataFactory.cpp
    src/data/data_file/DataFile.hpp
    src/data/data_file/DataFile.cpp)

set (MAIN_SRC
    app/Main.cpp
    src/comp/CompFactory.hpp
    src/view/ViewFactory.hpp
    src/data/DataFactory.hpp)

add_library (Comp SHARED ${COMP_SRC})
add_library (View SHARED ${VIEW_SRC})
add_library (Data SHARED ${DATA_SRC})
add_executable (${PROJECT_NAME} ${MAIN_SRC})
target_link_libraries (${PROJECT_NAME} Comp View Data)