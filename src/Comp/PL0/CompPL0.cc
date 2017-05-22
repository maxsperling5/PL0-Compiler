/************************/
/* Author: Max Sperling */
/************************/

#include "CompPL0.hh"

using namespace std;

ICompPtr IComp::create()
{
    return ICompPtr(new CompPL0());
}

bool CompPL0::init(IViewPtr viewPtr, IDataPtr dataPtr)
{
    this->viewPtr = viewPtr;
    this->dataPtr = dataPtr;

    lexPtr = new LexerPL0;
    parPtr = new ParserPL0;
    genPtr = new GeneratorPL0;

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

    string strCode = "";
    if(!dataPtr->read(strCode)) return false;

//    lexPtr->init();
//    parPtr->init(lexPtr);
//    genPtr->init(parPtr);
//    genPtr->exec();

    return true;
}
