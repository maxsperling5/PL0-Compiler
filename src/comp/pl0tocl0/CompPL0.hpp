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
    virtual bool init(pl0compiler::view::IViewUPtr viewUPtr, pl0compiler::data::IDataUPtr dataUPtr);
    virtual bool exec(int argc, char *argv[]);
    // ---------------

private:
    pl0compiler::view::IViewUPtr m_viewUPtr;
    pl0compiler::data::IDataUPtr m_dataUPtr;
};

} } }
