/************************/
/* Author: Max Sperling */
/************************/

#include "../src/pl0compiler/common/Logger.hpp"
#include "../src/pl0compiler/common/FileIO.hpp"
#include "../src/pl0compiler/compiler/Compiler.hpp"

int main(int argc, char *argv[])
{
    pl0compiler::common::Logger logger(pl0compiler::common::Logger::Level::Info);

    if (argc != 3)
    {
        logger.error("Usage: program <pl0-File> <cl0-File>\n");
        return 1;
    }
    pl0compiler::common::FileIO fileio(argv[1], argv[2]);

    pl0compiler::compiler::Compiler comp(logger, fileio);
    if (!comp.exec(argc, argv)) return 2;

    return 0;
}
