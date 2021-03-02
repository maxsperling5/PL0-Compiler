/************************/
/* Author: Max Sperling */
/************************/

#include "../src/pl0compiler/common/Logger.hpp"
#include "../src/pl0compiler/common/FileIO.hpp"
#include "../src/pl0compiler/common/Utils.hpp"
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
    std::string srcCode = "";
    if (!fileio.read(srcCode))
    {
        logger.error("Error while reading File");
        return 2;
    }

    pl0compiler::compiler::Compiler comp(logger);
    std::deque<char> binCode;
    if (!comp.exec(srcCode, binCode))
    {
        logger.error("Error while compiling");
        return 3;
    }

    logger.info(pl0compiler::common::toString(binCode));

    if (!fileio.write(binCode))
    {
        logger.error("Error while writing File");
        return 4;
    }

    return 0;
}
