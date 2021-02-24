#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "../IComp.hpp"

namespace pl0compiler { namespace comp { namespace pl0tocl0 {

class Tokenizer;
class Generator;

class CompPL0 : public IComp
{
public:
    CompPL0(){}
    ~CompPL0(){}

    // --- IComp -----
    virtual bool init(pl0compiler::view::IViewPtr viewPtr, pl0compiler::data::IDataPtr dataPtr);
    virtual bool exec(int argc, char *argv[]);
    // ---------------

private:
    pl0compiler::view::IViewPtr m_viewPtr;
    pl0compiler::data::IDataPtr m_dataPtr;

    Tokenizer *m_tokPtr;
    Generator *m_genPtr;
};

} } }
