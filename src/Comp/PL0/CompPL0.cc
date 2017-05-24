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

    tokPtr = new Tokenizer;
    genPtr = new Generator;

    string srcCode = "";
    if(!dataPtr->read(srcCode)) return false;

    vector<Token> token = tokPtr->exec(srcCode);
    vector<char> binary = genPtr->exec(token);

    viewPtr->write(binary);
    dataPtr->write(binary);

    delete tokPtr;
    delete genPtr;

    return true;
}
