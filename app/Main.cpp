/************************/
/* Author: Max Sperling */
/************************/

#include "../src/pl0compiler/common/Logger.hpp"
#include "../src/pl0compiler/common/FileIO.hpp"
#include "../src/pl0compiler/compiler/Compiler.hpp"

int main(int argc, char *argv[])
{
    pl0compiler::common::Logger logger(pl0compiler::common::Logger::Level::Info);
    pl0compiler::common::FileIO fileio;
    pl0compiler::compiler::Compiler comp(logger, fileio);

    if (!comp.exec(argc, argv)) return 1;
    return 0;
}
