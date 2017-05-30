cmake_minimum_required (VERSION 3.5)
project (PL0-Compiler)

set (PL0_HDR
	View/IView.hh
	View/CLI/ViewCLI.hh
	Data/IData.hh
	Data/File/DataFile.hh
	Comp/IComp.hh
	Comp/PL0/CompPL0.hh
	Comp/PL0/Tokenizer.hh
	Comp/PL0/Token.hh
	Comp/PL0/Generator.hh
	Comp/PL0/ILGen.hh
	Comp/PL0/Graph.hh
	Comp/PL0/Trans.hh
	Comp/PL0/Symbols.hh)

set (PL0_SRC
	Main.cc
	View/CLI/ViewCLI.cc
	Data/File/DataFile.cc
	Comp/PL0/CompPL0.cc
	Comp/PL0/Tokenizer.cc
	Comp/PL0/Token.cc
	Comp/PL0/Generator.cc
	Comp/PL0/ILGen.cc
	Comp/PL0/Graph.cc
	Comp/PL0/Trans.cc
	Comp/PL0/Symbols.cc)

add_executable (PL0-Compiler
	${PL0_SRC} ${PL0_HDR})