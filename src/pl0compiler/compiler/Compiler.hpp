#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "../common/Logger.hpp"
#include "../common/FileIO.hpp"

namespace pl0compiler { namespace compiler {

class Compiler
{
public:
    Compiler(common::Logger &logger, common::FileIO &fileio);

    bool exec(int argc, char *argv[]);

private:
    common::Logger &m_logger;
    common::FileIO &m_fileio;
};

} }
