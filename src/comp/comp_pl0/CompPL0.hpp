#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "../IComp.hpp"

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
    IViewPtr m_viewPtr;
    IDataPtr m_dataPtr;

    Tokenizer *m_tokPtr;
    Generator *m_genPtr;
};
