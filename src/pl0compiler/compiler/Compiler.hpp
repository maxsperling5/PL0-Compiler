#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "../logger/Logger.hpp"
#include "../fileio/FileIO.hpp"

namespace pl0compiler { namespace compiler {

class Compiler
{
public:
    Compiler(pl0compiler::logger::Logger &logger, pl0compiler::fileio::FileIO &fileio);

    bool exec(int argc, char *argv[]);

private:
    pl0compiler::logger::Logger &m_logger;
    pl0compiler::fileio::FileIO &m_fileio;
};

} }
