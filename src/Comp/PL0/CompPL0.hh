#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "../IComp.hh"

#include "LexerPL0.hh"
#include "ParserPL0.hh"
#include "GeneratorPL0.hh"

class CompPL0 : public IComp
{
public:
    CompPL0(){}
    ~CompPL0(){}

    // --- IComp -----------------------------
    virtual bool init(IViewPtr viewPtr, IDataPtr dataPtr);
    virtual bool exec(int argc, char *argv[]);
    // ---------------------------------------

private:
    IViewPtr viewPtr;
    IDataPtr dataPtr;

    LexerPL0 *lexPtr;
    ParserPL0 *parPtr;
    GeneratorPL0 *genPtr;
};
