/************************/
/* Author: Max Sperling */
/************************/

#include "CompPL0.hpp"

#include "Tokenizer.hpp"
#include "Generator.hpp"
#include "Token.hpp"
#include "CompEx.hpp"

using namespace std;

bool
pl0compiler::comp::pl0tocl0::CompPL0::init(pl0compiler::view::IViewUPtr viewUPtr, pl0compiler::data::IDataUPtr dataUPtr)
{
    m_viewUPtr = move(viewUPtr);
    m_dataUPtr = move(dataUPtr);

    return true;
}

bool
pl0compiler::comp::pl0tocl0::CompPL0::exec(int argc, char *argv[])
{
    if (!m_dataUPtr->init(argc, argv))
    {
        m_viewUPtr->write("Usage: program <pl0-File> <cl0-File>\n");
        return false;
    }

    string srcCode = "";
    if (!m_dataUPtr->read(srcCode))
    {
        m_viewUPtr->write("Error while reading File");
        return false;
    }

    m_tokPtr = new Tokenizer;
    m_genPtr = new Generator;

    deque<Token> token;
    try
    {
        m_tokPtr->exec(srcCode, token);
    }
    catch (...)
    {
        m_viewUPtr->write("Error while Tokenization");
        return false;
    }

    deque<char> binary;
    try
    {
        m_genPtr->exec(token, binary);
    }
    catch (CompEx &cex)
    {
        m_viewUPtr->write("Error while Generating");
        m_viewUPtr->write(cex.getError());
        return false;
    }

    m_viewUPtr->write(binary);

    if (!m_dataUPtr->write(binary))
    {
        m_viewUPtr->write("Error while writing File");
        return false;
    }

    delete m_tokPtr;
    delete m_genPtr;

    return true;
}
