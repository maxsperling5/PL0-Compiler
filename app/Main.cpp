/************************/
/* Author: Max Sperling */
/************************/

#include "../src/pl0compiler/logger/Logger.hpp"
#include "../src/pl0compiler/fileio/FileIO.hpp"
#include "../src/pl0compiler/compiler/Compiler.hpp"

int main(int argc, char *argv[])
{
    pl0compiler::logger::Logger logger;
    pl0compiler::fileio::FileIO fileio;
    pl0compiler::compiler::Compiler comp(logger, fileio);

    if (!comp.exec(argc, argv)) return 1;

    return 0;
}
