/************************/
/* Author: Max Sperling */
/************************/

#include "CompPL0.hpp"

#include "Tokenizer.hpp"
#include "Generator.hpp"
#include "Token.hpp"
#include "CompEx.hpp"

using namespace std;

bool CompPL0::init(IViewPtr viewPtr, IDataPtr dataPtr)
{
    m_viewPtr = viewPtr;
    m_dataPtr = dataPtr;

    return true;
}

bool CompPL0::exec(int argc, char *argv[])
{
    if(!m_dataPtr->init(argc, argv))
    {
        m_viewPtr->write("Usage: program <pl0-File> <cl0-File>\n");
        return false;
    }

    string srcCode = "";
    if(!m_dataPtr->read(srcCode))
    {
        m_viewPtr->write("Error while reading File");
        return false;
    }

    m_tokPtr = new Tokenizer;
    m_genPtr = new Generator;

    deque<Token> token;
    try{
        m_tokPtr->exec(srcCode, token);
    }
    catch(...){
        m_viewPtr->write("Error while Tokenization");
        return false;
    }

    deque<char> binary;
    try{
        m_genPtr->exec(token, binary);
    }catch(CompEx &cex){
        m_viewPtr->write("Error while Generating");
        m_viewPtr->write(cex.getError());
        return false;
    }

    m_viewPtr->write(binary);

    if(!m_dataPtr->write(binary))
    {
        m_viewPtr->write("Error while writing File");
        return false;
    }

    delete m_tokPtr;
    delete m_genPtr;

    return true;
}