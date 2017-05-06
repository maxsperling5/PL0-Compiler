project (PL0-Compiler)
SET(cmake_cxx_flags "${CMAKE_CXX_FLAGS} -std=c++11")
set(headers source/view/View.h
            source/view/CLI.h
            source/comp/comp.h
            source/comp/compPL0.h
            source/fread/FRead.h
            source/fread/FReadC.h
            source/lexer/Lexer.h
            source/lexer/LexerPL0.h
            source/lexer/Token.h)
set(sources source/main/Main.cpp
            source/view/CLI.cpp
            source/comp/compPL0.cpp
            source/fread/FReadC.cpp
            source/lexer/LexerPL0.cpp
            source/lexer/Token.cpp)
add_executable(PL0-Compiler ${sources} ${headers})