/************************/
/* Author: Max Sperling */
/************************/

#include "CompPL0.hh"

#include "Tokenizer.hh"
#include "Generator.hh"
#include "Token.hh"
#include "CompExcp.hh"

using namespace std;

ICompPtr IComp::create()
{
    return ICompPtr(new CompPL0());
}

bool CompPL0::init(IViewPtr viewPtr, IDataPtr dataPtr)
{
    this->viewPtr = viewPtr;
    this->dataPtr = dataPtr;

    return true;
}

bool CompPL0::exec(int argc, char *argv[])
{
    if(!dataPtr->init(argc, argv))
    {
        string strErr = "Usage: program \"<filepath/file>\"\n";
        viewPtr->write(strErr);
        return false;
    }

    string srcCode = "";
    if(!dataPtr->read(srcCode))
    {
        viewPtr->write("Error while reading File");
        return false;
    }

    tokPtr = new Tokenizer;
    genPtr = new Generator;

    deque<Token> token;
    try{
        tokPtr->exec(srcCode, token);
    }
    catch(...){
        viewPtr->write("Error while Tokenization");
        return false;
    }

    deque<char> binary;
    try{
        genPtr->exec(token, binary);
    }catch(CompExcp &compExcp){
        viewPtr->write("Error while Generating");
        viewPtr->write(compExcp.getError());
        return false;
    }

    viewPtr->write(binary);

    if(!dataPtr->write(binary))
    {
        viewPtr->write("Error while writing File");
        return false;
    }

    delete tokPtr;
    delete genPtr;

    return true;
}
