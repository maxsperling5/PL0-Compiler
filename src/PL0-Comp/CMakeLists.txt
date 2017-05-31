cmake_minimum_required (VERSION 3.5)
project (PL0-Compiler)

set (COMP_SRC
	Comp/PL0toCL0/CompPL0.hh
	Comp/PL0toCL0/CompPL0.cc
	Comp/PL0toCL0/Tokenizer.hh
	Comp/PL0toCL0/Tokenizer.cc
	Comp/PL0toCL0/Token.hh
	Comp/PL0toCL0/Token.cc
	Comp/PL0toCL0/Generator.hh
	Comp/PL0toCL0/Generator.cc
	Comp/PL0toCL0/ILGen.hh
	Comp/PL0toCL0/ILGen.cc
	Comp/PL0toCL0/Graph.hh
	Comp/PL0toCL0/Graph.cc
	Comp/PL0toCL0/Trans.hh
	Comp/PL0toCL0/Trans.cc
	Comp/PL0toCL0/Symbols.hh
	Comp/PL0toCL0/Symbols.cc
	Comp/PL0toCL0/CompExcp.hh
	Comp/PL0toCL0/CompExcp.cc)

set (VIEW_SRC
	View/CLI/ViewCLI.hh
	View/CLI/ViewCLI.cc)

set (DATA_SRC
	Data/File/DataFile.hh
	Data/File/DataFile.cc)

set (MAIN_SRC
	Main.cc
	Comp/IComp.hh
	View/IView.hh
	Data/IData.hh)

add_library (Comp SHARED ${COMP_SRC})
add_library (View SHARED ${VIEW_SRC})
add_library (Data SHARED ${DATA_SRC})
add_executable (PL0-Compiler ${MAIN_SRC})
target_link_libraries (PL0-Compiler Comp View Data)