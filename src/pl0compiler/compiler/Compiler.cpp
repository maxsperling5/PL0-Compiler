/************************/
/* Author: Max Sperling */
/************************/

#include "Compiler.hpp"

#include "Tokenizer.hpp"
#include "Generator.hpp"
#include "Token.hpp"
#include "CompEx.hpp"

namespace pl0compiler { namespace compiler {

Compiler::Compiler(common::Logger &logger) : m_logger(logger) {}

bool Compiler::exec(std::string &srcCode, std::deque<char> &binCode)
{
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

    binCode.clear();
    try
    {
        Generator generator;
        generator.exec(token, binCode);
    }
    catch (CompEx &cex)
    {
        m_logger.error("Error while Generating");
        m_logger.error(cex.getError());
        return false;
    }

    return true;
}

} }
