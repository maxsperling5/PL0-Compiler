cmake_minimum_required (VERSION 3.5)
project (PL0-Compiler)

set (SRC
  app/Main.cpp
  src/comp/IComp.hpp
  src/comp/comp_pl0/CompEx.cpp
  src/comp/comp_pl0/CompPL0.hpp
  src/comp/comp_pl0/Graph.cpp
  src/comp/comp_pl0/ILGen.hpp
  src/comp/comp_pl0/Token.cpp
  src/comp/comp_pl0/Tokenizer.hpp
  src/comp/comp_pl0/CompEx.hpp
  src/comp/comp_pl0/Generator.cpp
  src/comp/comp_pl0/Graph.hpp
  src/comp/comp_pl0/Symbols.cpp
  src/comp/comp_pl0/Token.hpp
  src/comp/comp_pl0/CompPL0.cpp
  src/comp/comp_pl0/Generator.hpp
  src/comp/comp_pl0/ILGen.cpp
  src/comp/comp_pl0/Symbols.hpp
  src/comp/comp_pl0/Tokenizer.cpp
  src/view/IView.hpp
  src/view/view_cli/ViewCLI.hpp
  src/view/view_cli/ViewCLI.cpp
  src/data/IData.hpp
  src/data/data_file/DataFile.hpp
  src/data/data_file/DataFile.cpp)

add_executable (${PROJECT_NAME} ${SRC})
