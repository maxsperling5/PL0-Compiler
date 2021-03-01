/************************/
/* Author: Max Sperling */
/************************/

#include "Compiler.hpp"

#include "Tokenizer.hpp"
#include "Generator.hpp"
#include "Token.hpp"
#include "CompEx.hpp"

namespace pl0compiler { namespace compiler {

Compiler::Compiler(pl0compiler::logger::Logger &logger, pl0compiler::fileio::FileIO &fileio) : m_logger(logger), m_fileio(fileio) {}

bool Compiler::exec(int argc, char *argv[])
{
    if (!m_fileio.init(argc, argv))
    {
        m_logger.write("Usage: program <pl0-File> <cl0-File>\n");
        return false;
    }

    std::string srcCode = "";
    if (!m_fileio.read(srcCode))
    {
        m_logger.write("Error while reading File");
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
        m_logger.write("Error while Tokenization");
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
        m_logger.write("Error while Generating");
        m_logger.write(cex.getError());
        return false;
    }

    m_logger.write(binary);

    if (!m_fileio.write(binary))
    {
        m_logger.write("Error while writing File");
        return false;
    }

    return true;
}

} }
