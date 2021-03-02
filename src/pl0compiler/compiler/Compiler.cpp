/************************/
/* Author: Max Sperling */
/************************/

#include "Compiler.hpp"

#include "Tokenizer.hpp"
#include "Generator.hpp"
#include "Token.hpp"
#include "CompEx.hpp"

#include "../common/Utils.hpp"

namespace pl0compiler { namespace compiler {

Compiler::Compiler(common::Logger &logger, common::FileIO &fileio) : m_logger(logger), m_fileio(fileio) {}

bool Compiler::exec(int argc, char *argv[])
{
    if (!m_fileio.init(argc, argv))
    {
        m_logger.error("Usage: program <pl0-File> <cl0-File>\n");
        return false;
    }

    std::string srcCode = "";
    if (!m_fileio.read(srcCode))
    {
        m_logger.error("Error while reading File");
        return false;
    }

    std::deque<Token> token;
    try
    {
        Tokenizer tokenizer;
        tokenizer.exec(srcCode, token);
    }
    catch (...)
    {
        m_logger.error("Error while Tokenization");
        return false;
    }

    std::deque<char> binary;
    try
    {
        Generator generator;
        generator.exec(token, binary);
    }
    catch (CompEx &cex)
    {
        m_logger.error("Error while Generating");
        m_logger.error(cex.getError());
        return false;
    }

    m_logger.info(common::toString(binary));

    if (!m_fileio.write(binary))
    {
        m_logger.error("Error while writing File");
        return false;
    }

    return true;
}

} }
