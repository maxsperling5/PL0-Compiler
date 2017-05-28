/************************/
/* Author: Max Sperling */
/************************/

#include "CompPL0.hh"

#include "Tokenizer.hh"
#include "Generator.hh"
#include "Token.hh"

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
    if(!dataPtr->read(srcCode)) return false;

    tokPtr = new Tokenizer;
    genPtr = new Generator;

    vector<Token> token;
    if(!tokPtr->exec(srcCode, token)) return false;
    vector<char> binary;
    if(!genPtr->exec(token, binary)) return false;

    viewPtr->write(binary);
    dataPtr->write(binary);

    delete tokPtr;
    delete genPtr;

    return true;
}
