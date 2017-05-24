#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "../IComp.hh"

class Tokenizer;
class Generator;

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

    Tokenizer *tokPtr;
    Generator *genPtr;
};
